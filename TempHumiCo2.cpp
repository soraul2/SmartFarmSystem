#include "TempHumiCo2.h"
#include <Arduino.h>

#define NO_ERROR 0

uint16_t TempHumiCo2::error = 0;
char TempHumiCo2::errorMessage[64] = {0};

void TempHumiCo2::begin() {
  //Wire 초기화
  Wire.begin();
  //sensor 초기화.
  sensor.begin(Wire, SCD41_I2C_ADDR_62);

  uint64_t serialNumber = 0;

  delay(30);
  // sensor에서 데이터를 가져온다.
  error = sensor.wakeUp();

  //error != 0 
  if (error != NO_ERROR) {
    Serial.print("Error trying to execute wakeUp(): ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
  }
  error = sensor.stopPeriodicMeasurement();
  if (error != NO_ERROR) {
    Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
  }
  error = sensor.reinit();
  if (error != NO_ERROR) {
    Serial.print("Error trying to execute reinit(): ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
  }
  // Read out information about the sensor
  error = sensor.getSerialNumber(serialNumber);
  if (error != NO_ERROR) {
    Serial.print("Error trying to execute getSerialNumber(): ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
    return;
  }
  Serial.print("serial number: 0x");
  PrintUint64(serialNumber);
  Serial.println();
}

void TempHumiCo2::PrintUint64(uint64_t& value){
    Serial.print("0x");
    Serial.print((uint32_t)(value >> 32), HEX);
    Serial.print((uint32_t)(value & 0xFFFFFFFF), HEX);
}


void TempHumiCo2::readSensor(){
  
  //센서를 읽음
  error = sensor.wakeUp();
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute wakeUp(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    //
    // Ignore first measurement after wake up.
    //
    error = sensor.measureSingleShot();
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute measureSingleShot(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    //
    // Perform single shot measurement and read data.
    //
    error = sensor.measureAndReadSingleShot(_co2, _temperature,
                                            _humidity);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute measureAndReadSingleShot(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }

}
float TempHumiCo2::getTemperature(){
  return _temperature;
}
float TempHumiCo2::getHumidity(){
  return _humidity;
}
uint16_t TempHumiCo2::getCo2(){
  return _co2;
}