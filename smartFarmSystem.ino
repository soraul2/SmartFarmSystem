//JSON 형식으로 변환하기 위한 라이브러리
#include <ArduinoJson.h>
//MQTT 및 WIFI 를 연결하기 위한 라이브러리
#include <PubSubClient.h>
#include <WiFiSSLClient.h>
#include <WiFiS3.h>

//NTP를 활용한 real time을 불러오는 라이브러리

#include <WiFiUdp.h>
#include <NTPClient.h>

#include "Enviroment.h"
#include "TempHumiCo2.h"
#include <Wire.h>
#include "Lux.h"
#include "Ph.h"
#include "WaterTemperature.h"
#include "Ec.h"



//MQTT 및 WIFI 를 연결하기 위한 DATA 설정
const char* ssid = "daesin_302";
const char* password = "ds123456";
const char* mqtt_server = "eafc441602df4e36aed5f15ad6df2e4c.s1.eu.hivemq.cloud";  // 예: "broker.hivemq.com"
const char* mqtt_topic = "smartfarm/data";                                        // 데이터를 보낼 토픽
const char* mqtt_client_id = "c9010a5344a54163aed93da0egfdgsbxcv";
const int mqtt_port = 8883;
const char* mqtt_user = "daesin_302";
const char* mqtt_password = "!Ds123456";


//제어 부분을 구독하는 데이터
const char* tempControlTopic = "smartfarmsystem/mycontrol/temperature";
const char* fanControlTopic = "smartfarmsystem/mycontrol/fan";
const char* phecControlTopic = "smartfarmsystem/mycontrol/phec";
const char* ledControlTopic = "smartfarmsystem/mycontrol/led";
const char* pumpControlTopic = "smartfarmsystem/mycontrol/pump";

const int tempPin = 12;
const int fanPin = 11;
const int phecPin = 10;
const int ledPin = 9;
const int pumpPin = 8;

//auto control은 어떤 방식으로 제어를 할 것인가?


// Wi-Fi와 MQTT 클라이언트 객체 생성
WiFiSSLClient sslClient;  // R4 보드용 SSL/TLS 클라이언트
PubSubClient client(sslClient);
TempHumiCo2 tempHumiCo2;
Lux lux;
//Ph ph;
Enviroment env;
WaterTemperature waterTemperature;
Ph ph(A0);
Ec ecSensor(A1);
// NTP 클라이언트 설정을 위한 UDP 객체 생성
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 32400, 60000);


// 현재 물의 온도 (온도 센서가 없으면 수동 입력)
float currentTemperature = 25.0;

void setup_wifi();
void reconnect();
void callback();

void setup() {
  Serial.begin(115200);

  //wifi 설정
  setup_wifi();

  // NTP 클라이언트 초기화
  timeClient.begin();
  timeClient.update();
  Serial.println("--- NTP Client initialized ---");

  // MQTT 서버 설정
  client.setServer(mqtt_server, mqtt_port);  // 기본 MQTT 포트 1883
  client.setCallback(callback);              // 콜백 함수 설정

  
  // 센서들 초기화
  Wire.begin();
  tempHumiCo2.begin();
  ph.begin();
  tempHumiCo2.readSensor();
  ecSensor.begin();


  // (선택 사항) 센서 교정
  // 실제 교정 용액을 사용해 얻은 아날로그 값과 온도를 입력합니다.
  // ecSensor.calibrate(1334.0, 25.0);

  Serial.println("--- Temp, Humi, Co2 Sensor begin() ---");

  while (!lux.begin()) {
    Serial.println("--- Lux Sensor 연결 X");
    delay(500);
  }
  Serial.println("--- Lux Sensor begin() ---");

  // Enviroment 객체에 고정적인 값(시리얼 번호 등)을 한 번만 설정
  env.setNum(1);
  env.setSerial("GRW-001-A");
  env.setMqttTopic("smartfarmsystem/enviroment");
}

// 센서 데이터 발행 간격 설정 (1분20초)
const long publishInterval = 62000;
unsigned long lastPublish = 0;

// 센서 데이터 읽는 시간 간격 설정 (1분)
const long readInterval = 60000;
unsigned long lastRead = 0;

// NTP 업데이트 시간 간격 설정 
const long ntpUpdateInterval = 32000;
unsigned long lastNtpUpdate = 0;

void loop() {


  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();

  if (now - lastRead >= readInterval) {
    lastRead = now;
    tempHumiCo2.readSensor();
  }

  if (now - lastPublish >= publishInterval) {
    lastPublish = now;
    timeClient.update();
    currentTemperature = waterTemperature.getWaterTemperature();
    env.setTemperature(tempHumiCo2.getTemperature());
    env.setHumidity(tempHumiCo2.getHumidity());
    env.setPh(ph.getPh());
    env.setEc(ecSensor.readEcValue(currentTemperature));
    env.setLux(lux.getLux());
    env.setWaterTemperature(waterTemperature.getWaterTemperature());
    env.setCo2((float)tempHumiCo2.getCo2());
    env.setLux(lux.getLux());
    // NTP를 사용하여 날짜 및 시간 데이터 설정
    env.setDate(timeClient.getFormattedTime());
    // JSON 형식으로 변환 및 MQTT 발행
    StaticJsonDocument<256> doc;
    env.toJson(doc);
    char jsonBuffer[256];
    serializeJson(doc, jsonBuffer);
    client.publish(env.getMqttTopic().c_str(), jsonBuffer);

    Serial.print("Published message: ");
    Serial.println(jsonBuffer);
  }
}


// Wi-Fi 연결 함수
void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// MQTT 연결 및 재연결 함수
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // MQTT 브로커에 연결 시도
    if (client.connect(mqtt_client_id, mqtt_user, mqtt_password)) {
      Serial.println("connected");
      // 성공적으로 연결되면 토픽 구독
      client.subscribe(tempControlTopic);
      client.subscribe(fanControlTopic);
      client.subscribe(phecControlTopic);
      client.subscribe(ledControlTopic);
      client.subscribe(pumpControlTopic);
      Serial.println("subscribed");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// 콜백 함수 선언 (메시지 수신 시 호출)
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("메시지 도착 [");
  Serial.print(topic);
  Serial.print("] ");

  // 수신된 페이로드를 문자열로 변환하여 출력
  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';  // 문자열의 끝을 표시



  if (strcmp(topic, "smartfarmsystem/mycontrol/temperature") == 0) {
    Serial.println("temperature 컨트롤 데이터 수신");
    if (strcmp(message, "true") == 0) {
      // LED 켜기
      pinMode(tempPin, OUTPUT);
      digitalWrite(tempPin, HIGH);
      Serial.println("Temperature ON");
      client.publish("smartfarmsystem/mycontrol/temperature/status", "true");
      // digitalWrite(LED_BUILTIN, HIGH);
    } else {
      pinMode(tempPin, OUTPUT);
      digitalWrite(tempPin, LOW);
      Serial.println("Temperature OFF");
      client.publish("smartfarmsystem/mycontrol/temperature/status", "false");
    }
  } else if (strcmp(topic, "smartfarmsystem/mycontrol/fan") == 0) {
    Serial.println("fan 컨트롤 데이터 수신");
    if (strcmp(message, "true") == 0) {
      // LED 켜기
      pinMode(fanPin, OUTPUT);
      digitalWrite(fanPin, HIGH);
      Serial.println("fan ON");
      client.publish("smartfarmsystem/mycontrol/fan/status", "true");
      // digitalWrite(LED_BUILTIN, HIGH);
    } else {
      pinMode(fanPin, OUTPUT);
      digitalWrite(fanPin, LOW);
      Serial.println("fan OFF");
      client.publish("smartfarmsystem/mycontrol/fan/status", "false");
    }
  } else if (strcmp(topic, "smartfarmsystem/mycontrol/phec") == 0) {
    Serial.println("phec 컨트롤 데이터 수신");
    if (strcmp(message, "true") == 0) {
      // LED 켜기
      pinMode(phecPin, OUTPUT);
      digitalWrite(phecPin, HIGH);
      Serial.println("phec ON");
      client.publish("smartfarmsystem/mycontrol/phec/status", "true");

      // digitalWrite(LED_BUILTIN, HIGH);
    } else {
      pinMode(phecPin, OUTPUT);
      digitalWrite(phecPin, LOW);
      Serial.println("phec OFF");
      client.publish("smartfarmsystem/mycontrol/phec/status", "false");
    }
  } else if (strcmp(topic, "smartfarmsystem/mycontrol/led") == 0) {
    Serial.println("led 컨트롤 데이터 수신");
    if (strcmp(message, "true") == 0) {
      // LED 켜기
      pinMode(ledPin, OUTPUT);
      digitalWrite(ledPin, HIGH);
      Serial.println("LED ON");
      client.publish("smartfarmsystem/mycontrol/led/status", "true");

      // digitalWrite(LED_BUILTIN, HIGH);
    } else {
      pinMode(ledPin, OUTPUT);
      digitalWrite(ledPin, LOW);
      Serial.println("LED OFF");
      client.publish("smartfarmsystem/mycontrol/led/status", "false");
    }
  } else if (strcmp(topic, "smartfarmsystem/mycontrol/pump") == 0) {
    Serial.println("pump 컨트롤 데이터 수신");
    if (strcmp(message, "true") == 0) {
      pinMode(pumpPin, OUTPUT);
      digitalWrite(pumpPin, HIGH);
      Serial.println("pump ON");
      client.publish("smartfarmsystem/mycontrol/pump/status", "true");
    } else {
      pinMode(pumpPin, OUTPUT);
      digitalWrite(pumpPin, LOW);
      Serial.println("pump OFF");
      client.publish("smartfarmsystem/mycontrol/pump/status", "false");
    }
  } else {
    Serial.println("알수 없는 데이터 수신");
  }
}
