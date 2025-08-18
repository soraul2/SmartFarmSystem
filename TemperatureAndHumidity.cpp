#include "TemperatureAndHumidity.h"
#define DHTTYPE DHT11

TemperatureAndHumidity(int pin)
  :_pin(pin),_dht(pin,DHTTYPE){
}

//main 함수 setup에서 초기화 필수
void TemperatureAndHumidity::init(){
  _dht.begin();
}
//getTemperature,getHumidity 실행 전에 readSensor() 실행
void TemperatureAndHumidity::readSensor(){
  float h = _dht.readHumidity();
  float t = _dht.readTemperature();

  //isnan() 함수를 사용하여 데이터 유효성 검사
  if(isnan(h) || isnan(t)){
    Serial.println("DHT 센서에서 값을 읽어오는 것을 실패하였습니다.");
  }else{
    _humidity = h;
    _temperature = t;
  }

}
float TemperatureAndHumidity::getTemperature(){
  return _temperature;
}
float TemperatureAndHumidity::getHumidity(){
  return _humidity;
}

