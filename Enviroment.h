#ifndef Enviroment_h
#define Enviroment_h

#include <Arduino.h>
#include <PubSubClient.h>

class Enviroment {
private:
  int _num;
  char _serial[50];
  char _mqttTopic[50]; // 포인터 대신 배열로 변경하여 메모리 안전성 확보
  float _temperature;
  float _humidity;
  float _ph;
  float _ec;
  float _waterTemperature;
  float _co2;
  float _lux;

public:
  // 생성자: 매개변수 순서와 타입을 명확하게 정의
  // .cpp 파일의 정의와 일치해야 함
  Enviroment(int num, const char* serial, float temperature, float humidity, float ph, float ec, float waterTemperature, float co2, float lux, const char* mqttTopic);

  // 데이터 전송 함수: const char*로 수정
  void sendData(const char* topic);

  // Getter 함수들
  int getNum() const;
  const char* getSerial() const;
  const char* getMqttTopic() const; // _mqttTopic을 반환하는 함수 추가
  float getTemperature() const;
  float getHumidity() const;
  float getPh() const;
  float getEc() const;
  float getWaterTemperature() const;
  float getCo2() const;
  float getLux() const;
};

#endif