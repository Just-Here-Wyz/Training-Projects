# 智能家居温湿度监测终端 / Smart Home Temperature & Humidity Monitor

基于 **ESP32-S3** 的环境监测终端：DHT11 采集温湿度，通过 MQTT 协议上报 **OneNET** 物联网平台，
并接收平台下发指令控制外设电源，同时以 FastLED 驱动灯珠做状态指示。

## 功能

- 每 10 秒采集一次温湿度并上报云端（物模型属性 `temp` / `humi` / `power`）
- 订阅平台指令主题，远程开关外设电源（GPIO2）
- WiFi / MQTT 断线自动重连，并输出连接错误码便于排查
- DHT11 读取失败自动重试 3 次，失败则跳过本次上报

## 硬件清单

| 元件 | 说明 |
|---|---|
| 主控 | ESP32-S3 |
| 温湿度传感器 | DHT11（单总线） |
| 状态指示 | FastLED 兼容灯珠（如 WS2812） |
| 外设电源 | GPIO2 驱动的继电器 / MOS 管 |

## 接线

| ESP32-S3 引脚 | 连接到 |
|---|---|
| GPIO8 | DHT11 DATA |
| GPIO2 | 外设电源控制端 |
| 3V3 / GND | DHT11 供电 |

## 目录结构

```
esp32-smart-home/
├── src/
│   ├── onenet_mqtt/     主程序：WiFi + MQTT + DHT11 完整实现
│   ├── dht11_basic/     DHT11 基础读取例程
│   └── fastled_demo/    FastLED 点灯例程
├── hardware/            嘉立创EDA 原理图与 PCB 工程（.eprj2 / .epro2）
└── docs/                调试过程记录与参考代码片段
```

## 编译与烧录

1. 使用 Arduino IDE 或 PlatformIO，开发板选择 **ESP32S3 Dev Module**
2. 安装依赖库：`DHT sensor library`（Adafruit）、`PubSubClient`、`FastLED`
3. 打开 `src/onenet_mqtt/onenet_mqtt.ino`
4. 替换文件顶部的三处占位符（WiFi 名称、WiFi 密码、OneNET 设备密钥）
5. 连接开发板并上传

## 关于 OneNET 设备密钥

设备密钥（token）形如 `version=2018-10-31&res=...&et=...&method=md5&sign=...`，
需登录 OneNET 控制台在设备详情中生成。注意 token 中的 `et` 为过期时间戳，
须设为**当前时间之后**，否则 MQTT 连接会返回错误码 `-5`（连接被拒绝）。

代码中保留的 `mqtt_devid`（设备名）与 `mqtt_pubid`（产品 ID）为示例值，
仅凭这两项无法接入平台，可按需替换为你自己的设备标识。

## 已知问题

- `docs/` 中的代码片段为早期版本的调试留存，其中引用的部件与主程序略有差异，仅供参考。
