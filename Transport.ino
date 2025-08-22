
// #include <WiFiS3.h>
// #include <PubSubClient.h>

// //wifi 이름 , 비밀번호
// const char* ssid = "daesin_302";
// const char* password = "ds123456";

// //broker ip 주소
// const char* mqtt_server = "192.168.0.78";

// //mapping
// const char* inTopic = "cks7349/LED";
// const char* colorTopic = "cks7349/Color";


// //WIFI 접속
// WiFiClient espClient;
// //MQTT 생성 및 접속 객체 생성
// PubSubClient client(espClient);

// // const int R = 3;
// // const int G = 5;
// // const int B = 6;

// // int rgb[3];



// void setup()
// {
//     Serial.begin(115200);
    
//     // pinMode(LED_BUILTIN, OUTPUT);
//     // digitalWrite(LED_BUILTIN, HIGH);

//     // pinMode(R, OUTPUT);
//     // pinMode(G, OUTPUT);
//     // pinMode(B, OUTPUT);
//     // digitalWrite(R, LOW);
//     // digitalWrite(G, LOW);
//     // digitalWrite(B, LOW);

//     //wifi 와 접속
//     setup_wifi();
//     //mqtt port와 broker ip 주소를 이용하여 클라이언트 서버 세팅
//     client.setServer(mqtt_server, 1883);
//     //데이터를 받아왔을 경우 call back 함수를 호출해야하는데 이 경우 client에 callback 함수를 세팅해줘야 한다.
//     client.setCallback(callback);
// }


// void loop()
// {   

//     //MQTT와 연결이 끊어졌을 경우 다시 재 접속을 시작한다.
//     if(!client.connected()) {
//         reconnect();
//     }
//     client.loop();



// }

// void setup_wifi()
// {
    
//     delay(10);
//     //ssid 와 비밀번호를 활용하여 WIFI 객체 초기화 작업 실시
//     WiFi.begin(ssid, password);
//     Serial.println();
//     Serial.print("Connecting to ");
//     Serial.println(ssid);

//     //현재 WIFI 접속 상태가 접속될떄까지 5초 기다리고 반복한다.
//     while(WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print('.');
//     }

//     //접속이 끝나면 실행된다.
//     Serial.println();
//     Serial.print("WiFi connected to ");
//     Serial.println(ssid);
//     Serial.print("IP address: ");
//     //WIFI 객체에 접속된 IP주소를 출력한다.
//     Serial.println(WiFi.localIP());
// }

// //MQTT로 브로커에 데이터를 보낼 수도 있지만 다시 받을수도 있기 때문에 항상 callback 함수를 정의하여
// //어떤 topic 에서 데이터를 받아 올지 대기를 해야한다.
// void callback(char* topic, byte* payload, unsigned int length)
// {   
//     //topic에서 데이터가 도착했을 경우 topic를 출력
//     Serial.print("Message arrived [");
//     Serial.print(topic);
//     Serial.print("] ");
    
//     //data 즉 payload의 크기를 받아서 0번째부터 length 번째 데이터를 출력시킨다.
//     for(int i=0; i<length; i++) {
//         Serial.print((char)payload[i]);
//     }
//     Serial.println();


//     // //만약 받은 topic과 내가 설정한 intopic이 같을 경우 어떤 프로그램 실행
//     // if(String(topic) == inTopic) {
//     //     if((char)payload[0] == '1') {
//     //         digitalWrite(LED_BUILTIN, LOW);
//     //     }
//     //     else {
//     //         digitalWrite(LED_BUILTIN, HIGH);
//     //     }
//     // }
//     // else if(String(topic) == colorTopic) {
//     //     for(int i=1; i<length; i++) {
//     //         Serial.print((char)payload[i]);
//     //         Serial.print("---------->");
//     //         Serial.println(hex2int((char)payload[i]));
//     //     }
//     //     for(int i=1; i<length; i+=2) {
//     //         rgb[i/2] = hex2int((char)payload[i])*16 + hex2int((char)payload[i+1]);
//     //         Serial.println(rgb[i/2]);
//     //     }
//     //     analogWrite(R, rgb[0]);
//     //     analogWrite(G, rgb[1]);
//     //     analogWrite(B, rgb[2]);
//     // }


// }

// int hex2int(char nibble)
// {
//     int value;
//     if('0'<=nibble && nibble<='9') {
//         value = nibble - '0';
//     }
//     else if('a'<=nibble && nibble<='f') {
//         value = nibble - 'a' + 10;
//     }

//     return value;
// }


// //MQTT 재연결
// void reconnect()
// {
//     //MQTT가 현재 연결되지 않았을 경우
//     while(!client.connected()) {
//         Serial.print("Attempting MQTT connection...");
//         Serial.println(mqtt_server);
//         //누가 데이터를 보냈는지 정해준다.
//         String clientID = "ESP32Client_";
//         //중복을 막기 위해 random 함수를 사용하여 clientID에 기타 문자를 추가해준다.
//         clientID += String(random(0xFFFF), HEX);

//         //MQTT와 연결을 새롭게 만든 clientID를 이용하여 접속을 실행한다.
//         if(client.connect(clientID.c_str()))  {
//             Serial.println("connected to ");
//             Serial.println(mqtt_server);  

//             //접속이 성공하면 토픽 두개를 구독한다.
//             //성공할 경우 connect의 객체가 true로 바뀌면서 다음 while문에서는 ! 연산자를 통해서 while문을 빠져나온다.
//             client.subscribe(inTopic);
//             client.subscribe(colorTopic);
//         }
//         else {
//             //접속이 실패하여 현재 클라이언트의 상태를 확인한다.
//             Serial.print("failed, rc=");
//             Serial.println(client.state());
//             Serial.println("try again in 5 seconds");
//             delay(5000);
//         }
//     }
// }
