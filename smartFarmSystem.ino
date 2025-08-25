// #include <WiFiS3.h>
// #include <PubSubClient.h>

// #include "Enviroment.h"
// #include <Arduino.h>

// // 와이파이 이름과 비밀번호
// const char* ssid = "daesin_302";
// const char* password = "ds123456";

// // MQTT 브로커 IP 주소
// const char* mqtt_server = "192.168.101.114";

// // 데이터 전송에 사용할 토픽 정의
// const char* temperatureTopic = "smartfarmsystem/enviroment/temperature";

// // WiFi 및 MQTT 클라이언트 객체
// WiFiClient espClient;
// PubSubClient client(espClient);

// // Enviroment 클래스 객체를 전역 변수로 선언
// // setup()과 loop() 모두에서 접근 가능하도록 함
// Enviroment* env;

// // 메인 파일에서 사용할 함수들을 미리 선언
// void setup_wifi();
// void reconnect();
// void callback(char* topic, byte* payload, unsigned int length);

// void setup() {
//   Serial.begin(115200);
//   Serial.println("--- Enviroment 클래스 테스트 시작 ---");

//   // 1. 테스트용 데이터를 준비
//   int testNum = 100;
//   const char* testSerial = "GRW-001-A";
//   float testTemperature = 25.5;
//   float testHumidity = 60.0;
//   float testPh = 6.5;
//   float testEc = 1.2;
//   float testWaterTemperature = 23.0;
//   float testCo2 = 450.0;
//   float testLux = 50000.0;
  
//   // 2. 데이터 정의 후에 클래스 객체를 초기화

//   // 'new' 키워드로 객체를 힙(heap) 메모리에 생성
//   env = new Enviroment(testNum, testSerial, testTemperature, testHumidity, testPh, testEc, testWaterTemperature, testCo2, testLux, temperatureTopic);
  
//   Serial.println("\n--- 게터 함수 테스트 ---");

//   // 3. 각 게터 함수가 올바른 값을 반환하는지 확인
//   // getNum() 테스트
//   if (env->getNum() == testNum) {
//     Serial.println("테스트 통과: getNum()");
//   } else {
//     Serial.print("테스트 실패: getNum(), 예상: ");
//     Serial.print(testNum);
//     Serial.print(", 실제: ");
//     Serial.println(env->getNum());
//   }

//   // getSerial() 테스트
//   if (strcmp(env->getSerial(), testSerial) == 0) {
//     Serial.println("테스트 통과: getSerial()");
//   } else {
//     Serial.print("테스트 실패: getSerial(), 예상: ");
//     Serial.print(testSerial);
//     Serial.print(", 실제: ");
//     Serial.println(env->getSerial());
//   }

//   // getTemperature() 테스트
//   if (abs(env->getTemperature() - testTemperature) < 0.001) {
//     Serial.println("테스트 통과: getTemperature()");
//   } else {
//     Serial.print("테스트 실패: getTemperature(), 예상: ");
//     Serial.print(testTemperature);
//     Serial.print(", 실제: ");
//     Serial.println(env->getTemperature());
//   }

//   // 나머지 게터 함수 테스트
//   if (abs(env->getHumidity() - testHumidity) < 0.001) Serial.println("테스트 통과: getHumidity()");
//   else Serial.println("테스트 실패: getHumidity()");

//   if (abs(env->getPh() - testPh) < 0.001) Serial.println("테스트 통과: getPh()");
//   else Serial.println("테스트 실패: getPh()");

//   if (abs(env->getEc() - testEc) < 0.001) Serial.println("테스트 통과: getEc()");
//   else Serial.println("테스트 실패: getEc()");

//   if (abs(env->getWaterTemperature() - testWaterTemperature) < 0.001) Serial.println("테스트 통과: getWaterTemperature()");
//   else Serial.println("테스트 실패: getWaterTemperature()");

//   if (abs(env->getCo2() - testCo2) < 0.001) Serial.println("테스트 통과: getCo2()");
//   else Serial.println("테스트 실패: getCo2()");

//   if (abs(env->getLux() - testLux) < 0.001) Serial.println("테스트 통과: getLux()");
//   else Serial.println("테스트 실패: getLux()");

//   Serial.println("\n--- 모든 테스트 종료 ---");
  
//   // 와이파이에 연결
//   setup_wifi();
//   // MQTT 브로커와 포트 설정
//   client.setServer(mqtt_server, 1883);
//   // 메시지 수신 시 호출할 콜백 함수 설정
//   client.setCallback(callback);

// }

// void loop() {
//   // MQTT 연결 상태를 확인하고, 끊어졌으면 재연결
//   if (!client.connected()) {
//     reconnect();
//   }
//   // MQTT 메시지를 확인하고 처리하는 핵심 함수
//   client.loop();

//   // Enviroment 클래스 내부의 sendData 함수를 호출
//   env->sendData("smartFarmSystem/enviroment");
//   delay(5000); // 5초마다 데이터 전송
// }

// void setup_wifi() {
//   delay(10);
//   WiFi.begin(ssid, password);
//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(ssid);

//   // 와이파이 연결 성공 시까지 대기
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print('.');
//   }

//   // 연결 성공 시 IP 주소 출력
//   Serial.println();
//   Serial.print("WiFi connected to ");
//   Serial.println(ssid);
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());
// }

// // MQTT 메시지를 수신했을 때 호출되는 함수
// void callback(char* topic, byte* payload, unsigned int length) {
//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.print("] ");

//   // 수신된 페이로드(데이터)를 시리얼 모니터에 출력
//   for (int i = 0; i < length; i++) {
//     Serial.print((char)payload[i]);
//   }
//   Serial.println();
// }

// // MQTT 브로커에 재연결하는 함수
// void reconnect() {
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     Serial.println(mqtt_server);
    
//     // 고유한 클라이언트 ID를 생성하여 연결 충돌 방지
//     String clientID = "ESP32Client_";
//     clientID += String(random(0xFFFF), HEX);

//     // MQTT 연결 시도
//     if (client.connect(clientID.c_str())) {
//       Serial.println("connected to ");
//       Serial.println(mqtt_server);
//       // NOTE: 메시지를 수신하려면 이 곳에서 토픽을 구독해야 합니다.
//     } else {
//       Serial.print("failed, rc=");
//       Serial.println(client.state());
//       Serial.println("try again in 5 seconds");
//       delay(5000);
//     }
//   }
// }