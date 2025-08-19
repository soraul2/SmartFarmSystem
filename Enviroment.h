#ifndef Enviroment_h
#define Enviroment_h

#include <Arduino.h>

class Enviroment {

private:
    int _num; 
    char _serial[50];
    float _temperature;
    float _humidity;
    float _ph;
    float _ec;
    float _waterTemperature;
    float _co2;
    float _lux;

public:
    // 생성자: num을 포함하고, serial을 const char* 타입으로 받음
    Enviroment(int num, const char* serial, float temperature, float humidity, float ph, float ec, float waterTemperature, float co2, float lux);
    
    
    int getNum() const;
    const char* getSerial() const;
    float getTemperature() const;
    float getHumidity() const;
    float getPh() const;
    float getEc() const;
    float getWaterTemperature() const;
    float getCo2() const;
    float getLux() const;


};

#endif