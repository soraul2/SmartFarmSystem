#ifndef Lux_h
#define Lux_h


#include <BH1750.h>
#include <Wire.h>

class Lux{
  
  public :

    Lux();
    void begin();
    float getLux();
    float readLux();

  private :

    float _lux;

    BH1750 _lightMeter;

};

#endif