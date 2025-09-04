#ifndef Enviroment_h
#define Enviroment_h
#include <ArduinoJson.h>

#include <Arduino.h>

class Enviroment {
private:
  int _num;
  String _serial;  // Arduino String 클래스를 사용하여 더 유연하게 변경
  String _mqttTopic;
  String _date;
  float _temperature;
  float _humidity;
  float _ph;
  float _ec;
  float _waterTemperature;
  float _co2;
  float _lux;

public:
  // 기본 생성자: 객체를 먼저 생성하고 데이터를 나중에 설정할 때 사용
  Enviroment();

  // 모든 데이터를 한 번에 설정하는 생성자
  Enviroment(int num, const String& serial, const String& date, float temp, float hum, float ph, float ec, float waterTemp, float co2, float lux, const String& mqttTopic);

  // 데이터 설정 (setter) 함수들
  void setNum(int num);
  void setSerial(const String& serial);
  void setDate(const String& date);
  void setMqttTopic(const String& topic);
  void setTemperature(float temp);
  void setHumidity(float hum);
  void setPh(float ph);
  void setEc(float ec);
  void setWaterTemperature(float waterTemp);
  void setCo2(float co2);
  void setLux(float lux);

  // 데이터 가져오기 (getter) 함수들
  int getNum() const;
  String getSerial() const;
  String getMqttTopic() const;
  String getDate() const;
  float getTemperature() const;
  float getHumidity() const;
  float getPh() const;
  float getEc() const;
  float getWaterTemperature() const;
  float getCo2() const;
  float getLux() const;
  void printAllData() const;
  void toJson(JsonDocument& doc);
};

#endif