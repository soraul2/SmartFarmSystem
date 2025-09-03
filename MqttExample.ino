// #include <SPI.h>
// #include <WiFi.h> // ESP8266/ESP32 보드는 <WiFi.h>를 사용하세요.
// #include <PubSubClient.h>

// // Wi-Fi 설정
// char ssid[] = "내_와이파이_이름"; // Wi-Fi 네트워크 이름
// char pass[] = "내_와이파이_비밀번호"; // Wi-Fi 비밀번호

// int status = WL_IDLE_STATUS;

// // MQTT 브로커 설정
// const char* mqtt_server = "broker.hivemq.com";
// const int mqtt_port = 1883;

// // 클라이언트 ID
// const char* clientID = "ArduinoPublisherClient";

// // Wi-Fi 클라이언트 객체 생성
// WiFiClient wifiClient;
// // PubSubClient 객체 생성
// PubSubClient client(wifiClient);

// long lastMsg = 0;
// char msg[50];
// int value = 0;

// void setup() {
//   Serial.begin(9600);

//   // Wi-Fi에 연결
//   while (status != WL_CONNECTED) {
//     Serial.print("Attempting to connect to SSID: ");
//     Serial.println(ssid);
//     status = WiFi.begin(ssid, pass);
//     delay(10000); // 10초 대기
//   }
//   Serial.println("Connected to Wi-Fi!");

//   // MQTT 브로커 설정
//   client.setServer(mqtt_server, mqtt_port);
// }

// void loop() {
//   // MQTT 브로커에 연결되지 않았다면 재연결 시도
//   if (!client.connected()) {
//     reconnect();
//   }
//   client.loop(); // MQTT 클라이언트의 통신 루프를 계속 실행

//   // 5초마다 메시지 발행
//   long now = millis();
//   if (now - lastMsg > 5000) {
//     lastMsg = now;

//     // 메시지 내용
//     ++value;
//     snprintf (msg, 50, "Hello from Arduino! #%d", value);
//     Serial.print("Publishing message: ");
//     Serial.println(msg);

//     // 메시지 발행 (토픽, 메시지)
//     client.publish("test/topic", msg);
//   }
// }

// // MQTT 브로커에 재연결하는 함수
// void reconnect() {
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
    
//     // MQTT 연결 시도
//     if (client.connect(clientID)) {
//       Serial.println("connected!");
//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//       delay(5000);
//     }
//   }
// }