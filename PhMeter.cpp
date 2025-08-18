#include "PhMeter.h"

const float ADC_VOLTAGE = 5.0;

PhMeter(int analogPin,float voltage,float offset,int samplingCount)
  :_analogPin(analogPin),_voltage(voltage),_offset(offset),_samplingCount(samplingCount)
{

}

void PhMeter::begin(){
  
}

float PhMeter::getPh(){
  int analogValue = analogRead(_analogPin);
  _voltage = analogValue * (ADC_VOLTAGE / 1024.0); //0-5V 범위로 전압 변환
  return calculatePh(_voltage);
}

float PhMeter::getAveragePh() {
    float sumPh = 0;
    
    for (int i = 0; i < _samplingCount; i++) {
        // analogRead()를 한 번만 호출
        int analogValue = analogRead(_analogPin);
        float voltage = analogValue * (ADC_VOLTAGE / 1024.0);
        sumPh += calculatePh(voltage);
        delay(10); // 센서 값 안정화를 위한 딜레이 (선택사항)
    }
    return sumPh / _samplingCount;
}

float PhMeter::calculatePh(float voltage){
  // 2.5V 일 때 pH 7.0 1V 당 pH 3.0 정도 변한다고 가정
  float ph = 7.0 - ((voltage - 2.5) * 3.0);
  return ph + _offset;
}