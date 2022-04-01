// This file contains all of the code relating to gathering velocity data from
// the accelerometer
#include "Kalman.h"
// Constants for moving point average
#define WINDOW_SIZE 20

// Define a struct to store the information needed for Moving Point Average
struct AccelInformation {
  int index = 0;
  double sum = 0;
  double reading[WINDOW_SIZE];
};
float velocity=0;
Kalman filt(10, 0.00001);
// Pin Assignments, these need to be assigned to analog pins
const int x_pin = A0;
const int y_pin = A1;
const int z_pin = A2;

// Constants for accelrometer readings
// TO-DO: Need to adjust the accel_offset number once we mount the accelerometer
// into its final position
double accel_offset = 0; 
const double prev_accel = 0;
double acceleration;

// Create an array of SensorInformation structs
struct AccelInformation accelerometer_readings;

// This is a helper function to get the acceleration in the x direction
double getXAcceleration() {
    acceleration = accel_offset - analogRead(x_pin);
    /*double filtered_acceleration = MovingPointAverage(accelerometer_readings.sum,
                                               accelerometer_readings.reading,
                                               accelerometer_readings.index,
                                               acceleration);*/
    double filtered_acceleration = filt.nextEstimate(acceleration);
    //Serial.println("X Accel: " + String(filtered_acceleration) + " ");
    return filtered_acceleration;
}

// This function updates the velocity global variable and returns the
// new updated value
float time1;
float time_since_last_reading;
void UpdateVelocity() {
    // Calculate the time since the last time reading
    float cur_time = millis();
    time_since_last_reading = (cur_time - time1);
    time1 = time_since_last_reading;
    double accel = 0 + getXAcceleration();
    velocity += accel * (time_since_last_reading / 1000);
    //Serial.println("Velocity: " + String(velocity));
}

void accleSetup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  getXAcceleration();
  accel_offset= -1*acceleration;

}

void AccelLoop() {
  //getXAcceleration();
  UpdateVelocity();
}
