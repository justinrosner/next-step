#include <Arduino.h>
#include "AUnit.h"
#include <UltraSonic.h>
#include <Lidar.h>

using aunit::TestRunner;

// Unit testing for Data collection suite: Ultrasonic Sensors
int const len=5;
int errorMarginUS = 5;
int threshold = 5;
int thresholdAngle = 5;
//UltraSonic s [len];

Lidar L;
int const buttonPin = 13;

int trig [len];
int echo [len];

void dataCollectionTestsSetup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);

  L=Lidar(10, 0.0001, 360, 13.9, 0.0001 , 19, 18);
  
  //s[0]=UltraSonic(28, 29, 15, 12.6, 10, 0.0001, 0.999, 72);//right
  //s[1]=UltraSonic(26, 27, 15, 12.6, 10, 0.0001, 0.999, 36); //centerright
  //s[2]=UltraSonic(24, 25, 15, 12.6, 10, 0.0001, 0.999, 0); //center
  //s[3]=UltraSonic(22, 23, 15, 12.6, 10, 0.0001, 0.999, 324); //centerleft
  //s[4]=UltraSonic(30, 31, 15, 12.6, 10, 0.0001, 0.999, 288); //left

  trig[0] = 28;
  trig[1] = 26;
  trig[2] = 24;
  trig[3] = 22;
  trig[4] = 30;
  echo[0] = 29;
  echo[1] = 27;
  echo[2] = 25;
  echo[3] = 23;
  echo[4] = 31;
  pinMode(trig[0], OUTPUT);
  pinMode(echo[0], INPUT);
  pinMode(trig[1], OUTPUT);
  pinMode(echo[1], INPUT);
  pinMode(trig[2], OUTPUT);
  pinMode(echo[2], INPUT);
  pinMode(trig[3], OUTPUT);
  pinMode(echo[3], INPUT);
  pinMode(trig[4], OUTPUT);
  pinMode(echo[4], INPUT);
}

// Test: 5.2.01
test(UltrasonicSensorReadingTest15cm) {
  // Object placed 15cm from sensor
  for (int i = 0; i < len; i++){

    if (readyNextTest()) {
      int dist = getDistanceFromSensor(trig[i]);
      int res = abs(dist-15);
      assertLessOrEqual(res, errorMarginUS);
    }
    
  }
}

// Test: 5.2.02
test(UltrasonicSensorReadingTest75cm) {
  // Object placed 75cm from sensor
  for (int i = 0; i < len; i++){

    if (readyNextTest()) {
      int dist = getDistanceFromSensor(trig[i]);
      int res = abs(dist-75);
      assertLessOrEqual(res, errorMarginUS);
    }
    
  }
}

// Test: 5.2.03
test(UltrasonicSensorReadingTest150cm) {
  // Object placed 150cm from sensor
  for (int i = 0; i < len; i++){

    if (readyNextTest()) {
      int dist = getDistanceFromSensor(trig[i]);
      int res = abs(dist-150);
      assertLessOrEqual(res, errorMarginUS);
    }
    
  }
}

// Test: 5.2.04
test(LidarReadingTest30cm) {
  // Object placed 150cm from sensor
  
  if (readyNextTest()) {
    for (int i = 0; i < sizeof(L.points); i++) {
      if (abs(L.points[i].angle - 300) <= thresholdAngle) {
        int res = abs(L.points[i].distance - 30);
        assertLessOrEqual(res, threshold);
      }
    }
  }
}

// Test: 5.2.05
test(LidarReadingTest100cm) {
  // Object placed 150cm from sensor
  
  if (readyNextTest()) {
    for (int i = 0; i < sizeof(L.points); i++) {
      if (abs(L.points[i].angle - 320) <= thresholdAngle) {
        int res = abs(L.points[i].distance - 100);
        assertLessOrEqual(res, threshold);
      }
    }
  }
}

// Test: 5.2.06
test(LidarReadingTest300cm) {
  // Object placed 150cm from sensor
  
  if (readyNextTest()) {
    for (int i = 0; i < sizeof(L.points); i++) {
      if (abs(L.points[i].angle - 360) <= thresholdAngle) {
        int res = abs(L.points[i].distance - 300);
        assertLessOrEqual(res, threshold);
      }
    }
  }
}

// Test: 5.2.07
test(LidarReadingTest600cm) {
  // Object placed 150cm from sensor
  
  if (readyNextTest()) {
    
    for (int i = 0; i < sizeof(L.points); i++) {
      if (abs(L.points[i].angle - 30) <= thresholdAngle) {
        int res = abs(L.points[i].distance - 600);
        assertLessOrEqual(res, threshold);
      }
    }
  }
}

// Test: 5.2.08
test(LidarReadingTest1000cm) {
  // Object placed 150cm from sensor
  
  if (readyNextTest()) {
    
    for (int i = 0; i < sizeof(L.points); i++) {
      if (abs(L.points[i].angle - 90) <= thresholdAngle) {
        int res = abs(L.points[i].distance - 1000);
        assertLessOrEqual(res, threshold);
      }
    }
  }
}

float getDistanceFromSensor(int sensorId) {
    digitalWrite(trig[sensorId], LOW);
    delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig[sensorId], HIGH);
    delayMicroseconds(10);
    digitalWrite(trig[sensorId], LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
    float duration = pulseIn(echo, HIGH);


    float distanceUS= duration*0.0343/2;

    return distanceUS;
}

bool readyNextTest() {
  bool flag = false;
  int buttonState = LOW;

  while (!flag) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH){
      flag = true;
    }
    
  }
  return flag;
}


void dataCollectionTestsLoop() {
  // put your main code here, to run repeatedly:
  L.sensorLoop();
  TestRunner::run();
}
