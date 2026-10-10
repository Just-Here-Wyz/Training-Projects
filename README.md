# Training-Projects / 实训项目合集

华北理工大学轻工学院 · 物联网工程专业 · 课程与实训项目归档

## 项目列表

| 目录 | 项目 | 方向 | 技术栈 |
|---|---|---|---|
| [esp32-smart-home](./esp32-smart-home/) | 智能家居温湿度监测终端<br>Smart Home Temperature & Humidity Monitor | 嵌入式 / 物联网 | ESP32-S3、Arduino、DHT11、FastLED、MQTT、OneNET、嘉立创EDA |
| [heima-travel](./heima-travel/) | 黑马旅游网<br>Heima Travel Website | Java Web 全栈 | Spring Boot 3、MyBatis-Plus、MySQL、Druid、Vue 3、Vite、Bootstrap |

## 关于敏感信息

开源版本中已移除全部真实凭据，统一替换为占位符。克隆后需自行填写：

| 占位符 | 所在文件 | 填写内容 |
|---|---|---|
| `YOUR_WIFI_SSID`<br>`YOUR_WIFI_PASSWORD` | `esp32-smart-home/src/onenet_mqtt/onenet_mqtt.ino` | 可用的 WiFi 名称与密码 |
| `YOUR_ONENET_TOKEN` | 同上 | OneNET 控制台生成的设备密钥 |
| `YOUR_DB_PASSWORD` | `heima-travel/backend/src/main/resources/application.yml` | 本机 MySQL 的 root 密码 |

## 说明

- 实训报告等个人文档（`.doc` / `.docx`）按要求不纳入本仓库。
- 各项目的硬件接线、运行步骤与已知问题，见对应目录下的 README。
