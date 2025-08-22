#include "RealTimeClock.h"

// 클래스 스코프 지정자 추가
RealTimeClock::RealTimeClock(int clk, int dat, int rst)
  : _clk(clk), _dat(dat), _rst(rst), _myWire(_dat, _clk, _rst), _rtc(_myWire) {
}

// 초기화
void RealTimeClock::begin() {
  _rtc.Begin();

  // RTC가 유효하지 않으면 컴파일 시간을 기준으로 시간을 설정
  if (!_rtc.IsDateTimeValid()) {
    _rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
  }
}

// 게터 함수에 const 추가
int RealTimeClock::getHour() {
  return _rtc.GetDateTime().Hour();
}
// 분을 가져오는 함수
int RealTimeClock::getMinute() {
  return _rtc.GetDateTime().Minute();
}
// 초를 가져오는 함수
int RealTimeClock::getSecond() {
  return _rtc.GetDateTime().Second();
}

/*
    // 컴파일 시간을 기반으로 'compiled' 객체 선언

    //초기 시간을 세팅하는 코드

    RtcDateTime compiled = RtcDateTime(2025,8,11,9,19,0);

    if (!Rtc.IsDateTimeValid()) {
        Serial.println("RTC의 시간이 유효하지 않습니다!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected()) {
        Serial.println("RTC가 쓰기 방지되어 있습니다. 쓰기 기능을 활성화합니다.");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning()) {
        Serial.println("RTC가 작동하지 않고 있습니다. 지금 시작합니다.");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) {
        Serial.println("RTC 시간이 컴파일 시간보다 이전입니다! (업데이트)");
        Rtc.SetDateTime(compiled);
    } else if (now > compiled) {
        Serial.println("RTC 시간이 컴파일 시간보다 최신입니다. (정상)");
    } else if (now == compiled) {
        Serial.println("RTC 시간이 컴파일 시간과 동일합니다! (정상)");
    }
  }
*/