#ifndef Ph_h
#define Ph_h

// pH 센서의 아날로그 핀
#define PH_PIN A0
// 아두이노 보드의 실제 전압을 측정하여 넣어주세요.
#define ADC_VOLTAGE 4.58
// 측정값 평균을 낼 횟수
#define NUM_SAMPLES 20

class Ph {

private:
  // 1단계 보정에서 얻은 값 (pH 6.86 기준)
  float ph_buffer_7 = 6.86;
  float voltage_buffer_7 = 2.70;

  // 2단계 보정에서 얻은 값 (pH 4.01 기준)
  float ph_buffer_4 = 4.01;
  float voltage_buffer_4 = 3.20;

  // 3단계 보정에서 얻은 값 (pH 9.18 기준)
  float ph_buffer_10 = 9.18;
  float voltage_buffer_10 = 2.31;

  // 기울기와 y절편 변수 (두 구간이므로 각각 필요)
  float slope1, intercept1; 
  float slope2, intercept2; 

public:
  // 생성자
  Ph(){
    slopeInterceptCal();
  }

  // 기울기 및 절편 계산 함수
  void slopeInterceptCal() {
    slope1 = (ph_buffer_4 - ph_buffer_7) / (voltage_buffer_4 - voltage_buffer_7);
    intercept1 = ph_buffer_7 - slope1 * voltage_buffer_7;

    slope2 = (ph_buffer_10 - ph_buffer_7) / (voltage_buffer_10 - voltage_buffer_7);
    intercept2 = ph_buffer_7 - slope2 * voltage_buffer_7;
  }

  // pH 값을 측정하여 반환하는 함수
  float getPh() {
    long sumOfSensorValues = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
      sumOfSensorValues += analogRead(PH_PIN);
      delay(10);
    }
    float averageSensorValue = (float)sumOfSensorValues / NUM_SAMPLES;
    float voltage = averageSensorValue * (ADC_VOLTAGE / 1024.0);

    float ph_value;

    if (voltage > voltage_buffer_7) {
      ph_value = slope1 * voltage + intercept1;
    } else {
      ph_value = slope2 * voltage + intercept2;
    }
    return ph_value;
  }
};

#endif