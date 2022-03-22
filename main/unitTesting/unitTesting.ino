#include <Arduino.h>
#include "AUnit.h"
#include <UltraSonic.h>

using aunit::TestRunner;

// Unit testing for Data collection suite: Ultrasonic Sensors
int const len=5;
UltraSonic s [len];

void setup() {
  // put your setup code here, to run once:
  s[0]=UltraSonic(28, 29, 15, 12.6, 10, 0.0001, 0.999, 72);//right
  s[1]=UltraSonic(26, 27, 15, 12.6, 10, 0.0001, 0.999, 36); //centerright
  s[2]=UltraSonic(24, 25, 15, 12.6, 10, 0.0001, 0.999, 0); //center
  s[3]=UltraSonic(22, 23, 15, 12.6, 10, 0.0001, 0.999, 324); //centerleft
  s[4]=UltraSonic(30, 31, 15, 12.6, 10, 0.0001, 0.999, 288); //left
}

test(UltrasonicSensors) {
  Serial.println("test1");
}

void loop() {
  // put your main code here, to run repeatedly:
  TestRunner::run();
}
