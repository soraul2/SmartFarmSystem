#include "Co2.h"

// 생성자 초기화 리스트 순서 수정
Co2::Co2(int rxPin, int txPin, int baudRate)
    : _rxPin(rxPin), _txPin(txPin), _cm1106(_rxPin, _txPin), _baudRate(baudRate), _co2(-1) {}

void Co2::begin() {
    _cm1106.begin(_baudRate);
}

int Co2::readSensor() {
    _cm1106.write(_cmdGetCo2, sizeof(_cmdGetCo2));
    delay(50); // 여기서는 간단히 delay 사용

    if (_cm1106.available() >= 4) {
        byte response[4];
        _cm1106.readBytes(response, 4);

        if (response[0] == 0x16) {
            _co2 = (response[1] << 8) | response[2];
            return _co2;
        }
    }
    _co2 = -1; // 실패 시 -1 반환
    return -1;
}

int Co2::getCo2() const {
    return _co2;
}