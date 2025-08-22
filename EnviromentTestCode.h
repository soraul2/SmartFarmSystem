/*

#include "Enviroment.h"
#include <Arduino.h>

void setup() {
  // 시리얼 통신 시작
  Serial.begin(9600);
  while (!Serial); // 시리얼 모니터가 열릴 때까지 기다림 (선택 사항)

  Serial.println("--- Enviroment 클래스 테스트 시작 ---");
  
  // 1. 테스트용 데이터 준비
  int testNum = 100;
  const char* testSerial = "GRW-001-A";
  float testTemperature = 25.5;
  float testHumidity = 60.0;
  float testPh = 6.5;
  float testEc = 1.2;
  float testWaterTemperature = 23.0;
  float testCo2 = 450.0;
  float testLux = 50000.0;

  // 2. 클래스 객체 생성 (생성자 테스트)
  Enviroment env(testNum, testSerial, testTemperature, testHumidity, testPh, testEc, testWaterTemperature, testCo2, testLux);

  Serial.println("\n--- 게터 함수 테스트 ---");

  // 3. 각 게터 함수가 올바른 값을 반환하는지 확인
  // getNum() 테스트
  if (env.getNum() == testNum) {
    Serial.println("테스트 통과: getNum()");
  } else {
    Serial.print("테스트 실패: getNum(), 예상: ");
    Serial.print(testNum);
    Serial.print(", 실제: ");
    Serial.println(env.getNum());
  }

  // getSerial() 테스트
  if (strcmp(env.getSerial(), testSerial) == 0) {
    Serial.println("테스트 통과: getSerial()");
  } else {
    Serial.print("테스트 실패: getSerial(), 예상: ");
    Serial.print(testSerial);
    Serial.print(", 실제: ");
    Serial.println(env.getSerial());
  }

  // getTemperature() 테스트
  if (abs(env.getTemperature() - testTemperature) < 0.001) {
    Serial.println("테스트 통과: getTemperature()");
  } else {
    Serial.print("테스트 실패: getTemperature(), 예상: ");
    Serial.print(testTemperature);
    Serial.print(", 실제: ");
    Serial.println(env.getTemperature());
  }

  // 모든 게터 함수에 대해 동일한 방식으로 테스트 진행
  if (abs(env.getHumidity() - testHumidity) < 0.001) Serial.println("테스트 통과: getHumidity()");
  else Serial.println("테스트 실패: getHumidity()");

  if (abs(env.getPh() - testPh) < 0.001) Serial.println("테스트 통과: getPh()");
  else Serial.println("테스트 실패: getPh()");

  if (abs(env.getEc() - testEc) < 0.001) Serial.println("테스트 통과: getEc()");
  else Serial.println("테스트 실패: getEc()");
  
  if (abs(env.getWaterTemperature() - testWaterTemperature) < 0.001) Serial.println("테스트 통과: getWaterTemperature()");
  else Serial.println("테스트 실패: getWaterTemperature()");
  
  if (abs(env.getCo2() - testCo2) < 0.001) Serial.println("테스트 통과: getCo2()");
  else Serial.println("테스트 실패: getCo2()");
  
  if (abs(env.getLux() - testLux) < 0.001) Serial.println("테스트 통과: getLux()");
  else Serial.println("테스트 실패: getLux()");
  
  Serial.println("\n--- 모든 테스트 종료 ---");
}

void loop() {
  // 테스트는 setup()에서 한 번만 실행
}

*/