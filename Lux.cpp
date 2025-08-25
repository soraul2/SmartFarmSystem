#include "Lux.h"

//pin은 반드시 (SDA)A4 , (SCL)A5 에 꽂아야 한다. 생성자에는 해당 핀 번호가 들어가지 않는다.
Lux::Lux() {
  
}

//반드시 센서값을 받기 전에 begin()을 사용하여 센서에서 과연 값을 받고 있는지 받고 있지 않은지 setup() 함수에서 실행시켜줘야 한다.
//while 문을 활용하여 연결될때까지 반복 하는 방식을 추천한다.
bool Lux::begin() {
  return _veml.begin();
}

// _lux 값이 갱신돼고 값을 받아서 넣는다. -1 일 경우 ERROR
float Lux::getLux() {
  _lux = _veml.readLux();
  // 센서가 빠졌거나 비정상적인 값을 반환할 경우
  if (_lux < 0 || _lux > 150000) { // 120000 lux를 초과하는 값은 비정상으로 간주
    return -1; // 오류를 나타내는 값으로 반환
  }
  return _lux;
}



/* Test CODE

//1. Lux (VEML 7700 센서 테스트)
//반드시 A4 A5에 꽂아야 한다.
#include "Arduino.h"
#include "Lux.h"

Lux lux;

void setup(){
  Serial.begin(9600);
  //조도 센서 연결 -> 실행
  while(!lux.begin()){
    Serial.println("--- Lux Sensor 연결 X");
  }
  
}

void loop(){
  
  float currLux = lux.getLux();
  Serial.println(currLux);
  delay(3000);

}



*/