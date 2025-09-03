#include "Enviroment.h"

// 기본 생성자 정의
Enviroment::Enviroment() {}

// 모든 데이터를 한 번에 설정하는 생성자
Enviroment::Enviroment(int num, const String& serial, float temp, float hum, float ph, float ec, float waterTemp, float co2, float lux, const String& mqttTopic)
  : _num(num), _serial(serial), _mqttTopic(mqttTopic), _temperature(temp), _humidity(hum), _ph(ph), _ec(ec), _waterTemperature(waterTemp), _co2(co2), _lux(lux) {}

// 데이터 설정 (setter) 함수들
void Enviroment::setNum(int num) {
  _num = num;
}

void Enviroment::setSerial(const String& serial) {
  _serial = serial;
}

void Enviroment::setMqttTopic(const String& topic) {
  _mqttTopic = topic;
}

void Enviroment::setTemperature(float temp) {
  _temperature = temp;
}

void Enviroment::setHumidity(float hum) {
  _humidity = hum;
}

void Enviroment::setPh(float ph) {
  _ph = ph;
}

void Enviroment::setEc(float ec) {
  _ec = ec;
}

void Enviroment::setWaterTemperature(float waterTemp) {
  _waterTemperature = waterTemp;
}

void Enviroment::setCo2(float co2) {
  _co2 = co2;
}

void Enviroment::setLux(float lux) {
  _lux = lux;
}

// 데이터 가져오기 (getter) 함수들
int Enviroment::getNum() const {
  return _num;
}

String Enviroment::getSerial() const {
  return _serial;
}

String Enviroment::getMqttTopic() const {
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

// **추가된 부분**
// 모든 데이터를 시리얼 모니터로 출력
void Enviroment::printAllData() const {
  Serial.println("--- Enviroment Data ---");
  Serial.print("Num: ");
  Serial.println(_num);
  Serial.print("Serial: ");
  Serial.println(_serial);
  Serial.print("MQTT Topic: ");
  Serial.println(_mqttTopic);
  Serial.print("Temperature: ");
  Serial.println(_temperature);
  Serial.print("Humidity: ");
  Serial.println(_humidity);
  Serial.print("pH: ");
  Serial.println(_ph);
  Serial.print("EC: ");
  Serial.println(_ec);
  Serial.print("Water Temperature: ");
  Serial.println(_waterTemperature);
  Serial.print("CO2: ");
  Serial.println(_co2);
  Serial.print("Lux: ");
  Serial.println(_lux);
  Serial.println("-----------------------");
}


void Enviroment::toJson(JsonDocument& doc){
  doc["num"] = _num;
  doc["serial"] = _serial;
  doc["temperature"] = _temperature;
  doc["humidity"] = _humidity;
  doc["waterTemperature"] = _waterTemperature;
  doc["co2"] = _co2;
  doc["lux"] = _lux;
  doc["ph"] = _ph;
  doc["ec"] = _ec;
}



