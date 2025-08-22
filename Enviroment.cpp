#include "Enviroment.h"
#include <string.h>
#include <ArduinoJson.h>

extern PubSubClient client;

// 생성자 정의
Enviroment::Enviroment(int num, const char* serial, float temperature, float humidity, float ph, float ec, float waterTemperature, float co2, float lux, const char* mqttTopic)
  : _num(num), _temperature(temperature), _humidity(humidity), _ph(ph), _ec(ec), _waterTemperature(waterTemperature), _co2(co2), _lux(lux) {

  strncpy(_serial, serial, sizeof(_serial) - 1);
  _serial[sizeof(_serial) - 1] = '\0';

  strncpy(_mqttTopic, mqttTopic, sizeof(_mqttTopic) - 1);
  _mqttTopic[sizeof(_mqttTopic) - 1] = '\0';
}

void Enviroment::sendData(const char* topic) {
  DynamicJsonDocument doc(512);

  doc["num"] = _num;
  doc["serial"] = _serial;
  doc["temperature"] = _temperature;
  doc["humidity"] = _humidity;
  doc["ph"] = _ph;
  doc["ec"] = _ec;
  doc["waterTemperature"] = _waterTemperature;
  doc["co2"] = _co2;
  doc["lux"] = _lux;

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);

  client.publish(topic, jsonBuffer);
}

// **이 부분이 빠져있을 가능성이 높습니다. 아래 코드를 추가하세요.**
int Enviroment::getNum() const {
  return _num;
}

const char* Enviroment::getSerial() const {
  return _serial;
}

const char* Enviroment::getMqttTopic() const {
  return _mqttTopic;
}

float Enviroment::getTemperature() const {
  return _temperature;
}

float Enviroment::getHumidity() const {
  return _humidity;
}

float Enviroment::getPh() const {
  return _ph;
}

float Enviroment::getEc() const {
  return _ec;
}

float Enviroment::getWaterTemperature() const {
  return _waterTemperature;
}

float Enviroment::getCo2() const {
  return _co2;
}

float Enviroment::getLux() const {
  return _lux;
}