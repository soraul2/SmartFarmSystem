#ifndef REALTIMECLOCK_H
#define REALTIMECLOCK_H

#include <ThreeWire.h>
#include <RtcDS1302.h>

class RealTimeClock {
public:
    RealTimeClock(int clk, int dat, int rst);
    void begin();
    // const 한정자 제거
    int getHour();
    int getMinute();
    int getSecond();

private:
    int _clk;
    int _dat;
    int _rst;
    ThreeWire _myWire;
    RtcDS1302<ThreeWire> _rtc;
};

#endif