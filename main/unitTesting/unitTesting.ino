#include <Arduino.h>
#include "AUnit.h"
#include "UltraSonic.h"
#include "Lidar.h"

using aunit::TestRunner;

int const buttonPin = 8;
Lidar L=Lidar(10, 0.0001, 360, 13.9, 0.0001 , 19, 18);

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);

  TestRunner::exclude("Lidar*");
  TestRunner::exclude("LeftHapticMotorTest");
  TestRunner::exclude("CenterLeftHapticMotorTest");
  TestRunner::exclude("CenterHapticMotorTest");
  TestRunner::exclude("CenterRightHapticMotorTest");
  TestRunner::exclude("RightHapticMotorTest");
  TestRunner::exclude("ReboundAngleCalculationTest");
  TestRunner::exclude("NoObjectPresentTest");
  TestRunner::exclude("NearingWallTest");
  TestRunner::exclude("UpdatingBubbleBoundaryChangingSpeed");
  TestRunner::exclude("UpdatingBubbleBoundaryStandingStill");
  TestRunner::exclude("UpdatingBubbleBoundaryMaximalSpeed");
  TestRunner::exclude("UpdatingBubbleBoundaryMaximalSpeed");
  TestRunner::exclude("UltrasonicSensorReadingTest150cm");
  TestRunner::exclude("UltrasonicSensorReadingTest500cm");
  // put your setup code here, to run once:
  dataCollectionTestsSetup();
  objectAvoidanceTestsSetup();
  UserGuidanceSystemTestsSetup();
}

void loop() {
  
  //L.sensorLoop();
  TestRunner::run();

}

bool readyNextTest() {
  bool flag = false;
  int buttonState = LOW;

  while (flag == false) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH){
      flag = true;
    }
    
  }
  return flag;
}
