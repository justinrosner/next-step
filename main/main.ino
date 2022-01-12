#include <LiquidCrystal.h>

#include <Mouse.h>

#include <Arduino.h>
#include "Talkie.h"
#include <RPLidar.h>

#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
// This pin should connected with the RPLIDAR's MOTOCTRL signal
//////////////////////////////////////////////////////////////////////////////

// You need to create an driver instance
RPLidar lidar;

int nsbit = 0;

int trigPin = 7;
int echoPin = 5;
int trigPin2 = 4;
int echoPin2 = 3;

float minDistance = 100000;
float angleAtMinDist = 0;


void setup() {
  lidar.begin(Serial);

  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);

}

void loop() { 
  mic();
  run_lidar();
}
