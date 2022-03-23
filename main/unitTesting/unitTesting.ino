#include <Arduino.h>

void setup() {
  dataCollectionTestsSetup();
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("-----Running Test Suite-----");
  Serial.println("dataCollectionTests START");
  dataCollectionTestsLoop();
  Serial.println("dataCollectionTests END");
  Serial.println("-----End of Test Run-----");
}
