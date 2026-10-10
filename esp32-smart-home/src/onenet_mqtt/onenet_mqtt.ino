#include <Arduino.h>
#include "WiFi.h"
#include "PubSubClient.h"
#include <DHT.h>

// ================== WiFi 配置 ==================
// ⚠️ 安全提示：真实 WiFi 名称与密码已从开源版本中移除，请自行填写。
const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

// ================== OneNET MQTT 配置 ==================
const char *mqtt_server = "183.230.40.96";
const int port = 1883;
#define mqtt_devid "chuanganqi"
#define mqtt_pubid "C32LMhC81i"
// ⚠️ 安全提示：mqtt_password 为设备密钥（token），已从开源版本中移除。
//    获取方式：登录 OneNET 控制台 → 设备详情 → 密钥，复制后替换下面整行。
//    注意：token 中的 et 时间戳需设为当前时间 + 7 天以内，
//    否则连接会返回错误码 -5（连接被拒绝）。
#define mqtt_password "YOUR_ONENET_TOKEN"

// ================== DHT11 传感器（接 GPIO8） ==================
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// 电源控制引脚（GPIO2）
#define POWER_PIN 2
int real_power = 0;

// ================== MQTT 主题（注意大小写必须与平台一致） ==================
#define TOPIC_POST "$sys/C32LMhC81i/chuanganqi/thing/property/post"
#define TOPIC_SET "$sys/C32LMhC81i/chuanganqi/thing/property/set"
#define TOPIC_SET_REPLY "$sys/C32LMhC81i/chuanganqi/thing/property/set/reply"

WiFiClient espClient;
PubSubClient client(espClient);

char msgJson[256];
// ★ 物模型属性名：temp、humi、power（请确保在平台已定义）
char dataTemplate[] = "{\"id\":\"%lu\",\"version\":\"1.0\",\"params\":{\"temp\":{\"value\":%.1f},\"humi\":{\"value\":%.1f},\"power\":{\"value\":%d}}}";

// 非阻塞定时（替代 Ticker，避免中断冲突）
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 10000; // 10 秒

// ================== 连接 WiFi ==================
void setupWifi() {
  Serial.println("连接 WiFi...");
  WiFi.begin(ssid, password);
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry++ < 30) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi 连接成功");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi 连接失败，请检查密码和 SSID");
  }
}

// ================== MQTT 回调（处理平台下发指令） ==================
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.println("\n收到平台下发指令:");
  Serial.println(topic);
  String recvMsg;
  for (size_t i = 0; i < length; i++) recvMsg += (char)payload[i];
  Serial.println("原始报文: " + recvMsg);

  // 解析 power 值（简单解析，假设 JSON 格式固定）
  int powerPos = recvMsg.indexOf("\"power\"");
  if (powerPos != -1) {
    int valuePos = recvMsg.indexOf("\"value\"", powerPos);
    if (valuePos != -1) {
      int colon = recvMsg.indexOf(":", valuePos);
      if (colon != -1) {
        int numStart = colon + 1;
        while (recvMsg[numStart] == ' ' || recvMsg[numStart] == '\t') numStart++;
        int numEnd = numStart;
        while (numEnd < recvMsg.length() && (isdigit(recvMsg[numEnd]) || recvMsg[numEnd] == '-')) numEnd++;
        if (numEnd > numStart) {
          real_power = recvMsg.substring(numStart, numEnd).toInt();
          Serial.print("更新电源值: ");
          Serial.println(real_power);
          digitalWrite(POWER_PIN, real_power > 0 ? HIGH : LOW);
        }
      }
    }
  }

  // 发送指令应答（必须）
  String idStr = "";
  int idStart = recvMsg.indexOf("\"id\":\"") + 6;
  int idEnd = recvMsg.indexOf("\"", idStart);
  if (idStart > 0 && idEnd > idStart) idStr = recvMsg.substring(idStart, idEnd);
  char replyBuf[100];
  snprintf(replyBuf, sizeof(replyBuf), "{\"id\":\"%s\",\"code\":0,\"msg\":\"success\"}", idStr.c_str());
  client.publish(TOPIC_SET_REPLY, replyBuf);
  Serial.println("已发送指令应答");
}

// ================== 读取并上报温湿度 ==================
void sendTempAndHumi() {
  if (!client.connected()) {
    Serial.println("MQTT 未连接，跳过上报");
    return;
  }

  // 读取 DHT11（带 3 次重试）
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int retry = 3;
  while ((isnan(t) || isnan(h)) && retry-- > 0) {
    delay(100);
    t = dht.readTemperature();
    h = dht.readHumidity();
  }
  if (isnan(t) || isnan(h)) {
    Serial.println("⚠️ 传感器读取失败，跳过本次上报");
    return;
  }

  // 串口实时显示
  Serial.print("【实时温湿度】 温度: ");
  Serial.print(t);
  Serial.print(" °C, 湿度: ");
  Serial.print(h);
  Serial.println(" %");

  // 组装 JSON（id 使用毫秒时间戳，保证唯一）
  unsigned long id = millis();
  snprintf(msgJson, sizeof(msgJson), dataTemplate, id, t, h, real_power);
  Serial.print("上报数据: ");
  Serial.println(msgJson);

  // 发布并检查结果
  boolean ret = client.publish(TOPIC_POST, msgJson);
  if (ret) {
    Serial.println(">>> 发布成功 <<<");
  } else {
    Serial.println(">>> 发布失败！请检查网络和主题 <<<");
  }
}

// ================== MQTT 重连（带错误码输出） ==================
void clientReconnect() {
  int tryCount = 0;
  while (!client.connected() && tryCount++ < 5) {
    Serial.print("重连 MQTT (尝试 ");
    Serial.print(tryCount);
    Serial.print(")...");
    if (client.connect(mqtt_devid, mqtt_pubid, mqtt_password)) {
      Serial.println("成功");
      client.subscribe(TOPIC_SET);
      return;
    } else {
      Serial.print("失败，错误码: ");
      Serial.println(client.state());
      Serial.println("5秒后重试");
      delay(5000);
    }
  }
  Serial.println("重连放弃，稍后重试");
}

// ================== setup ==================
void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, LOW);

  dht.begin();
  setupWifi();

  client.setServer(mqtt_server, port);
  client.setCallback(callback);

  // 首次连接 MQTT
  Serial.print("首次连接 MQTT...");
  if (client.connect(mqtt_devid, mqtt_pubid, mqtt_password)) {
    Serial.println("成功");
    client.subscribe(TOPIC_SET);
  } else {
    Serial.print("失败，错误码: ");
    Serial.println(client.state());
  }
}

// ================== loop ==================
void loop() {
  // WiFi 断线重连
  if (WiFi.status() != WL_CONNECTED) {
    setupWifi();
  }
  // MQTT 断线重连
  if (!client.connected()) {
    clientReconnect();
  }
  client.loop();  // 维持心跳和接收消息

  // 定时上报（非阻塞）
  if (millis() - lastSendTime >= sendInterval) {
    lastSendTime = millis();
    sendTempAndHumi();
  }
}