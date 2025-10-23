#ifndef Ec_h
#define Ec_h

#include "Arduino.h"

class Ec {
  public:
    // 생성자: EC 센서 핀 번호를 설정합니다.
    Ec(int pin);

    // EC 값을 읽는 함수
    float readEcValue();

    // 온도에 따른 EC 값을 읽는 함수 (온도 보상)
    float readEcValue(float temperature);

  private:
    int _ecPin; // EC 센서가 연결된 핀
    
    // 교정 값 설정
    const float _calibrationAnalogValue = 350.0;
    const float _calibrationEcValue = 12880.0;
    const float _fixedTemperature = 25.0;
};

#endif