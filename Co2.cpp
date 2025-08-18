#include "Co2.h"

Co2::Co2(int rxPin, int txPin, int baudRate)
  : _rxPin(rxPin), _txPin(txPin), _cm1106(_rxPin, txPin), _baudRate(baudRate) {
    _cmdGetCo2[0] = 0x11;
    _cmdGetCo2[1] = 0x01;
    _cmdGetCo2[2] = 0x01;
    _cmdGetCo2[3] = 0xED;
}

void Co2::begin() {
  _cm1106.begin(_baudRate);
}

void Co2::readSensor() {
  _cm1106.write(_cmdGetCo2, sizeof(_cmdGetCo2));
  delay(50);

  if (_cm1106.available() >= 4) {
    byte response[4];
    _cm1106.readBytes(response, 4);
    if (response[0] == 0x16) {
      _co2 = (response[1] << 8) | response[2];
    } else {
      _co2 = -1; // 잘못된 응답 시 오류 값 할당
    }
  } else {
    _co2 = -1; // 응답이 없을 시 오류 값 할당
  }
}

int Co2::getCo2() {
  return _co2;
}