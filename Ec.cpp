#include "Ec.h"

// 생성자
Ec::Ec(int pin) {
  _ecPin = pin;
}

// EC 값을 읽는 함수 (25도 고정)
float Ec::readEcValue() {
  return readEcValue(_fixedTemperature);
}

// EC 값을 읽는 함수 (온도 보상)
float Ec::readEcValue(float temperature) {
  // 아날로그 값 읽기
  float rawAnalogValue = analogRead(_ecPin);
  float ecVoltage = rawAnalogValue * 5.0 / 1024.0; 
  
  // 교정 값으로 EC 값 계산
  float ec = (ecVoltage * _calibrationEcValue) / (_calibrationAnalogValue * 5.0 / 1024.0);
  
  // 온도 보정
  ec = ec / (1.0 + 0.02 * (temperature - _fixedTemperature));
  
  return ec;
}