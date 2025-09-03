#ifndef WaterTemperature_h
#define WaterTemperature_h

#include <OneWire.h>
#include <DallasTemperature.h>


// 데이터(DAT) 핀이 연결된 디지털 핀 번호
#define ONE_WIRE_BUS 2

// OneWire와 DallasTemperature 라이브러리 인스턴스 생성
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


class WaterTemperature {

private:
  float _waterTemperature;
public:
  WaterTemperature() {
    
  }
  float getWaterTemperature() {
    sensors.begin();
    sensors.requestTemperatures();
    _waterTemperature = sensors.getTempCByIndex(0);

    if (_waterTemperature == DEVICE_DISCONNECTED_C) {
      Serial.println("센서가 연결되지 않았습니다.");
    }
    return _waterTemperature;
  }
};


#endif
