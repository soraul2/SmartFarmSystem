// #include "TempHumiCo2.h"
// #include <Wire.h>

// // TempHumiCo2 클래스 객체 생성
// TempHumiCo2 mySensor;

// void setup() {
//   Serial.begin(115200);
//   while (!Serial) {
//     // Wait for serial connection to be established.
//     delay(100);
//   }
  
//   Serial.println("SCD41 Periodic Measurement Test");
  
//   // Initialize I2C communication.
//   Wire.begin();

//   // Initialize the sensor.
//   mySensor.begin();
  
//   Serial.println("Sensor initialization complete. Starting measurements...");
// }

// void loop() {
//   // Read sensor data.
//   // This function updates the class's member variables when data is ready (every 5 seconds).
//   mySensor.readSensor();

//   // Get the updated values and print to the Serial Monitor.
//   Serial.print("CO2: ");
//   Serial.print(mySensor.getCo2());
//   Serial.print(" ppm | ");
//   Serial.print("Temp: ");
//   Serial.print(mySensor.getTemperature());
//   Serial.print(" C | ");
//   Serial.print("Humidity: ");
//   Serial.print(mySensor.getHumidity());
//   Serial.println(" %RH");
  
//   // Wait for 1 second before the next loop.
//   // The sensor updates every 5 seconds, so this allows us to check for new data periodically.
//   delay(1000); 
// }
