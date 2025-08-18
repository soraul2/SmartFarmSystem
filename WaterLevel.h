#ifndef WaterLevel_h
#define WaterLevel_h

class WaterLevel {

public:

  WaterLevel(int pin)
    : _pin(pin) {
  }

  void begin(){
    pinMode(_pin,INPUT);
  }
  
  //수위센서 장착 부위에 물이 닿았을 경우 true , 닿지 않을 경우 false
  bool getWaterLevelCheck(){ 
    return digitalRead(_pin);
  }

private:
  int _pin;
};

#endif