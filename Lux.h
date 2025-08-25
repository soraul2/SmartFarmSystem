#ifndef Lux_h
#define Lux_h

//사용 센서 : VEML7700
#include <Wire.h>
#include <Adafruit_VEML7700.h>

class Lux{

  private : 
    //실질적인 광량을 저장하는 부분
    float _lux;
    //VEML 라이브러리를 사용하여 실질적으로 광량을 읽어주는 부분
    Adafruit_VEML7700 _veml;

  public :
    //pin은 반드시 (SDA)A4 , (SCL)A5 에 꽂아야 한다. 생성자에는 해당 핀 번호가 들어가지 않는다.
    Lux();
    //초기화 작업을 해줘야한다.
    bool begin();
    //getLux를 하기 전에 readSensor을 무조건 해줘야 getLux가 갱신이 돼서 값을 받아올 수 있다.
    float getLux();

};

#endif