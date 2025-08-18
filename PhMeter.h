#ifndef PhMeter_h
#define PhMeter_h

class PhMeter{

  public :
    
    PhMeter(int analogPin,float voltage,float offset,int samplingCount);

    void begin();
    float getPh();
    float getAveragePh();
    float calculatePh(float voltage);

  private :

    int _analogPin;
    //아두이노 전원 전압
    float _voltage;
    //pH 센서 보정용 오프셋 값
    float _offset;
    //샘플링 횟수
    int _samplingCount;
};

#endif