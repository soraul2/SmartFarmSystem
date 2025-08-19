#ifndef Co2_h
#define Co2_h

#include <SoftwareSerial.h>
#include <Arduino.h> // <--- 이 줄을 추가해야 'byte' 타입을 인식합니다.


class Co2 {
public:
    Co2(int rxPin, int txPin, int baudRate);
    void begin();
    int readSensor(); // 값을 반환하도록 변경
    int getCo2() const; // 상수 함수로 변경

private:
    int _co2;
    SoftwareSerial _cm1106;
    int _rxPin;
    int _txPin;
    const byte _cmdGetCo2[4] = {0x11, 0x01, 0x01, 0xED}; // 배열 크기 명시 및 const로 변경
    int _baudRate;
};

#endif