//모든 데이터를 받아서 전송할 환경 클래스
#include "Enviroment.h"
//Co2 , humi , temp
#include "TempHumiCo2.h"
#include <Wire.h>
//Lux
#include "Lux.h"
//ph
#include "PhMeter.h"
//date
#include "RealTimeClock.h"
//ec (부품 X)
//waterTemp (부품 X)

//객체 생성
//온도 , 습도 , Co2 관련 세팅 반드시 A4 , A5에 꽂아야 한다.
TempHumiCo2 tempHumiCo2;

//Lux 관련 세팅
//pin은 반드시 (SDA)A4 , (SCL)A5 에 꽂아야 한다
Lux lux;

//ph 관련 세팅
PhMeter phMeter(A0,9.1,10);
RealTimeClock rtc(5,6,7);

//환경을 받을 Enviroment
Enviroment* env;

void setup() {
  Serial.begin(9600);
  //온도 , 습도 , Co2 관련 세팅
  Wire.begin();
  tempHumiCo2.begin();
  Serial.println("--- Temp , Humi , Co2 Sensor begin() ---");

  //Lux 초기화 작업을 해줘야한다.
  while(!lux.begin()){
    Serial.println("--- Lux Sensor 연결 X");
  }
  //phMeter 초기화 작업을 해준다.
  phMeter.begin();

  //rtc
  rtc.begin();
}

void loop() {
  //온도 , 습도 , Co2 센서를 읽어서 값을 가져오는 단계
  tempHumiCo2.readSensor();
  
  env = new Enviroment(1, "GRW-001-A", tempHumiCo2.getTemperature(), tempHumiCo2.getHumidity(), phMeter.getAveragePh(), 1.0, 25.0, (float)tempHumiCo2.getCo2(), lux.getLux(), "smartfarmsystem/enviroment");
  //  Enviroment(int num, const char* serial, float temperature, float humidity, float ph, float ec, float waterTemperature, float co2, float lux, const char* mqttTopic);
  Serial.println(env->getCo2());
  Serial.println(env->getTemperature());
  Serial.println(env->getHumidity());
  Serial.println(env->getLux());
  Serial.println(env->getPh());
  Serial.println(rtc.getSecond());
  delay(3000);
}




