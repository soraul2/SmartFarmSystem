#ifndef TemperatureAndHumidity_h
#define TemperatureAndHumidity_h

#include <Arduino.h> // 아두이노 기본 라이브러리 추가
#include <DHT.h>

class TemperatureAndHumidity{
public :
    // DHTTYPE을 생성자 매개변수로 받거나, 내부 상수로 정의
    TemperatureAndHumidity(int pin, int type = DHT11);

    void init();
    void readSensor();
    float getTemperature() const; // const 추가
    float getHumidity() const; // const 추가

private :
    int _pin;
    float _temperature;
    float _humidity;
    DHT _dht;
};

#endif