#ifndef PhMeter_h
#define PhMeter_h

#include <Arduino.h>

class PhMeter {

public:
  // 생성자: 전원 전압은 상수로 처리하고, offset과 samplingCount만 받음
  PhMeter(int analogPin, float offset, int samplingCount);

  void begin();
  float getPh() const;         // 게터 함수에 const 추가
  float getAveragePh() const;  // 게터 함수에 const 추가

private:
  // ADC 전압은 상수로 선언
  const float ADC_VOLTAGE = 5.0;

  int _analogPin;
  float _offset;
  int _samplingCount;

  // 계산 로직은 private 멤버 함수로
  float _calculatePh(float voltage) const;
};

#endif


/*
#include "PhMeter.h"

PhMeter phMeter(A0,9.1,10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  phMeter.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(phMeter.getAveragePh());
  delay(2000);

}


*/