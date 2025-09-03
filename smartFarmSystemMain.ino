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

//객체 생성 - loop() 밖에서 한 번만 생성
TempHumiCo2 tempHumiCo2;
Lux lux;
Ph ph;

// Enviroment 클래스의 객체를 전역 변수로 선언
// setter를 사용하면 생성자에 모든 값을 넣을 필요가 없습니다.
Enviroment env; 

WaterTemperature waterTemperature;

void setup() {
  Serial.begin(9600);
  
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

  delay(2000);

}