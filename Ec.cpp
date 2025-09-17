#include "Ec.h"

// 생성자: EC 센서 핀 번호를 초기화합니다.
Ec::Ec(int pin) {
    _ecPin = pin;
    _calibrationValue = 1334.0; // 기본 교정 값
    _calibrationTemp = 25.0; // 기본 교정 온도
}

// 센서 초기화 (시리얼 통신 시작)
void Ec::begin() {
    Serial.begin(115200);
}

// 교정 값을 설정하는 메서드
void Ec::calibrate(float analogValue, float temp) {
    _calibrationValue = analogValue;
    _calibrationTemp = temp;
}

// EC 값을 읽는 메서드
float Ec::readEcValue(float temperature) {
    // 아날로그 값 읽기
    float rawAnalogValue = analogRead(_ecPin);
    
    // 증류수에서 측정한 0점 기준값
    float zeroPointAnalogValue = 17.0; 
    
    // 아날로그 값이 0점 값보다 작으면 0으로 간주
    if (rawAnalogValue <= zeroPointAnalogValue) {
        return 0.0;
    }
    
    // 0점 값을 뺀 실제 측정 아날로그 값
    float compensatedAnalogValue = rawAnalogValue - zeroPointAnalogValue;
    
    // 0점 보정된 아날로그 값을 전압(V)으로 변환
    float ecVoltage = compensatedAnalogValue * 5.0 / (1024.0 - zeroPointAnalogValue);
    
    // 전도도 계산
    // 이 공식은 교정 용액이 없을 때 임시로 사용하는 근사식입니다.
    // DFRobot 기준, 1413 uS/cm은 약 1.334V에 해당합니다. (아날로그 값 273)
    float ecValue = ecVoltage * (1413.0 / 1.334); 
    
    // 온도 보정
    ecValue = ecValue / (1.0 + 0.02 * (temperature - _calibrationTemp));
    
    return ecValue;
}