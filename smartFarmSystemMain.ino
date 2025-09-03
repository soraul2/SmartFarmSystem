//모든 데이터를 받아서 전송할 환경 클래스
#include "Enviroment.h"
//Co2 , humi , temp
#include "TempHumiCo2.h"
#include <Wire.h>
//Lux
#include "Lux.h"
//ph
#include "Ph.h"
//ec (부품 X)
//waterTemp (부품 X)
#include "WaterTemperature.h"

//JSON 형식으로 변환하기 위한 라이브러리
#include <ArduinoJson.h>

//MQTT 및 WIFI 를 연결하기 위한 라이브러리
#include <WiFi.h>
#include <PubSubClient.h>
//MQTT 및 WIFI 를 연결하기 위한 DATA 설정
// Wi-Fi 설정
const char* ssid = "daesin_302";
const char* password = "ds123456";

// MQTT 브로커 설정
const char* mqtt_server = "YOUR_MQTT_BROKER_IP_OR_DOMAIN"; // 예: "broker.hivemq.com"
const char* mqtt_topic = "smartfarm/data"; // 데이터를 보낼 토픽

// MQTT 클라이언트 ID
const char* mqtt_client_id = "ESP32_SmartFarm_Client";

// Wi-Fi와 MQTT 클라이언트 객체 생성
WiFiClient espClient;
PubSubClient client(espClient);

// 함수 선언
void setup_wifi();
void reconnect();

//객체 생성 - loop() 밖에서 한 번만 생성
TempHumiCo2 tempHumiCo2;
Lux lux;
Ph ph;

// Enviroment 클래스의 객체를 전역 변수로 선언
// setter를 사용하면 생성자에 모든 값을 넣을 필요가 없습니다.
Enviroment env; 

WaterTemperature waterTemperature;

void setup() {
  Serial.begin(115200);
  
  //wifi 설정
  setup_wifi();
  
  // MQTT 서버 설정
  client.setServer(mqtt_server, 1883); // 기본 MQTT 포트 1883

  // 센서들 초기화
  Wire.begin();
  tempHumiCo2.begin();
  Serial.println("--- Temp, Humi, Co2 Sensor begin() ---");

  while(!lux.begin()){
    Serial.println("--- Lux Sensor 연결 X");
    delay(500);
  }
  Serial.println("--- Lux Sensor begin() ---");

  // Enviroment 객체에 고정적인 값(시리얼 번호 등)을 한 번만 설정
  env.setNum(1);
  env.setSerial("GRW-001-A");
  env.setMqttTopic("smartfarmsystem/enviroment");
}

void loop() {
   // MQTT 연결 상태 확인 및 재연결
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // MQTT 클라이언트 루프, 메시지 수신 등을 처리
  // 센서에서 현재 데이터를 읽어옴
  tempHumiCo2.readSensor();
  
  // setter를 사용하여 env 객체의 값을 업데이트
  env.setTemperature(tempHumiCo2.getTemperature());
  env.setHumidity(tempHumiCo2.getHumidity());
  env.setPh(ph.getPh());
  
  // EC 및 수온은 임시 값으로 설정 (부품이 있다면 해당 센서 함수로 변경)
  env.setEc(1.0);
  env.setWaterTemperature(waterTemperature.getWaterTemperature());
  
  env.setCo2((float)tempHumiCo2.getCo2());
  env.setLux(lux.getLux());

  env.printAllData();

  //json 형식으로 변환 시작
  StaticJsonDocument<256> doc;
  env.toJson(doc);

  char jsonBuffer[256];
  serializeJson(doc , jsonBuffer);

  //MQTT 브로커에 데이터 발행
  client.publish(env.getMqttTopic().c_str(),jsonBuffer);
  Serial.print("Published message: ");
  Serial.println(jsonBuffer);

  delay(2000);
}



// Wi-Fi 연결 함수
void setup_wifi() {
  delay(10);
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
    if (client.connect(mqtt_client_id)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}