#include "TemperatureAndHumidity.h"
#include <Arduino.h> // Serial.println()과 isnan()을 위해 추가

// 생성자 정의에 클래스 스코프 지정자 추가
TemperatureAndHumidity::TemperatureAndHumidity(int pin, int type)
    : _pin(pin), _dht(pin, type) {
    // 생성자 본문은 비워둡니다.
}

void TemperatureAndHumidity::init(){
    _dht.begin();
}

void TemperatureAndHumidity::readSensor(){
    float h = _dht.readHumidity();
    float t = _dht.readTemperature();

    if (isnan(h) || isnan(t)){
        Serial.println("DHT 센서에서 값을 읽어오는 것을 실패하였습니다.");
        _humidity = NAN; // 실패 시 유효하지 않은 값 할당
        _temperature = NAN; // 실패 시 유효하지 않은 값 할당
    } else {
        _humidity = h;
        _temperature = t;
    }
}

float TemperatureAndHumidity::getTemperature() const {
    return _temperature;
}

float TemperatureAndHumidity::getHumidity() const {
    return _humidity;
}