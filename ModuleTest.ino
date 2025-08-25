#include "Arduino.h"
#include "TempHumiCo2.h"

TempHumiCo2 tempHumiCo2;

void setup(){
  Serial.begin(9600);

  while(!tempHumiCo2.begin()){
    //온습도이산화탄소 센서에서 값을 받아올때까지 반복
    Serial.println("센서 장착 X");
    delay(3000);
  }
  //온도 , 습도 , 이산화탄소 초기값 입력
  tempHumiCo2.readSensor();

}

void loop(){
  delay(3000);
  
  float temperature = tempHumiCo2.getTemperature();
  float humidity = tempHumiCo2.getHumidity();
  uint16_t co2 = tempHumiCo2.getCo2();
  
  Serial.println(temperature);
  
  Serial.println(humidity);
  
  Serial.println(co2);
}

