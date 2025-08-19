#include "Enviroment.h"
#include <string.h>

// 생성자 정의: 헤더 파일과 동일하게 매개변수 리스트를 수정
Enviroment::Enviroment(int num, const char* serial, float temperature, float humidity, float ph, float ec, float waterTemperature, float co2, float lux)
    : _num(num), _temperature(temperature), _humidity(humidity), _ph(ph), _ec(ec), _waterTemperature(waterTemperature), _co2(co2), _lux(lux) { // <-- 여기에 콤마를 추가했습니다.

    strncpy(_serial, serial, sizeof(_serial) - 1);
    _serial[sizeof(_serial) - 1] = '\0';
}

// 나머지 함수들은 그대로 유지됩니다.
int Enviroment::getNum() const {
    return _num;
}

const char* Enviroment::getSerial() const {
    return _serial;
}

float Enviroment::getTemperature() const {
    return _temperature;
}

float Enviroment::getHumidity() const {
    return _humidity;
}

float Enviroment::getPh() const {
    return _ph;
}

float Enviroment::getEc() const {
    return _ec;
}

float Enviroment::getWaterTemperature() const {
    return _waterTemperature;
}

float Enviroment::getCo2() const {
    return _co2;
}

float Enviroment::getLux() const {
    return _lux;
}