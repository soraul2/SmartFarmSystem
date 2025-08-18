
#ifndef Co2_h
#define Co2_h

#include <SoftwareSerial.h>

class Co2 {

public:
  Co2(int rxPin, int txPin,int baudRate);
  void readSensor();
  void begin();
  int getCo2();

private:

  int _co2;
  SoftwareSerial _cm1106;
  int _rxPin;
  int _txPin;
  byte _cmdGetCo2[];
  int _baudRate;
};

#endif