#ifndef TempHumiCo2_h
#define TempHumiCo2_h

#include <SensirionI2cScd4x.h>
#include <Wire.h>

class TempHumiCo2{

  private :
    SensirionI2cScd4x sensor;
    
    static char errorMessage[64];
    static uint16_t error;

    float _temperature;
    float _humidity;
    uint16_t _co2;


  public :  
    void begin();
    void readSensor();
    float getTemperature();
    float getHumidity();
    uint16_t getCo2();
    void PrintUint64(uint64_t& value);


};

#endif