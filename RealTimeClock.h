#ifndef RealTimeClock_h
#define RealTimeClock_h

#include "Arduino.h"
#include <ThreeWire.h>
#include <RtcDS1302.h>

//현실 시간을 불러오는 클래스
class RealTimeClock{

  public :
    //생성자에 필요한 것 CLK , DAT , RST
    RealTimeClock(int clk , int dat , int rst);

    void begin();

    int getHour();
    int getMinute();
    int getSecond();

  private :
    
    int _clk;
    int _dat;
    int _rst;

    ThreeWire _myWire;
    RtcDS1302<ThreeWire> _rtc;

};

#endif