#include "PhMeter.h"

// 생성자 정의: 클래스 스코프 PhMeter:: 추가
PhMeter::PhMeter(int analogPin, float offset, int samplingCount)
  :_analogPin(analogPin), _offset(offset), _samplingCount(samplingCount)
{
    // 생성자 본문은 비워둡니다.
}

void PhMeter::begin(){
    // 필요한 초기화 코드를 추가할 수 있습니다.
}

float PhMeter::getPh() const {
    // 내부 변수를 수정하지 않고, 계산만 수행
    int analogValue = analogRead(_analogPin);
    float voltage = analogValue * (ADC_VOLTAGE / 1024.0);
    return _calculatePh(voltage);
}

float PhMeter::getAveragePh() const {
    float sumPh = 0;
    
    for (int i = 0; i < _samplingCount; i++) {
        int analogValue = analogRead(_analogPin);
        float voltage = analogValue * (ADC_VOLTAGE / 1024.0);
        sumPh += _calculatePh(voltage);
        delay(10);
    }
    return sumPh / _samplingCount;
}

float PhMeter::_calculatePh(float voltage) const {
    float ph = 7.0 - ((voltage - 2.5) * 4.38);
    return ph + _offset;
}