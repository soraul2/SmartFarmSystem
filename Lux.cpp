#include "Lux.h"

Lux::Lux()
  : _lightMeter() {
}

//setup에 초기화를 무조건 시켜줘야 한다.
void Lux::begin() {
  _lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  //BH1750::CONTINUOUS_HIGH_RES_MODE고해상도 모드로 초기화
}

float Lux::getLux() {
  _lux = _lightMeter.readLightLevel();
  if (_lux != -1.0) {
    return _lux;
  } else {
    Serial.println("센서에서 값을 읽는 데 실패했습니다.");
    return -1.0;
  }
}
