#ifndef TemperatureAndHumidity_h
#define TemperatureAndHumidity_h

#include <DHT.h>

class TemperatureAndHumidity{
  
  public :
    
    TemperatureAndHumidity(int pin);

    void init();
    void readSensor();
    float getTemperature();
    float getHumidity();

  private :
    int _pin;
    float _temperature;
    float _humidity;
    DHT _dht;

};

#endif