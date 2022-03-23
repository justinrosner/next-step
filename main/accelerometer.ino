// This file contains all of the code relating to gathering velocity data from
// the accelerometer

// Constants for moving point average
#define WINDOW_SIZE 20

// Define a struct to store the information needed for Moving Point Average
struct AccelInformation {
  int index = 0;
  double sum = 0;
  double reading[WINDOW_SIZE];
};

// Pin Assignments, these need to be assigned to analog pins
const int x_pin = A0;
const int y_pin = A1;
const int z_pin = A2;

// Constants for accelrometer readings
// TO-DO: Need to adjust the accel_offset number once we mount the accelerometer
// into its final position
const double accel_offset = 355.0; 
const double prev_accel = 0;

// Create an array of SensorInformation structs
struct AccelInformation accelerometer_readings;

// This is a helper function to get the acceleration in the x direction
double getXAcceleration() {
    double acceleration = accel_offset - analogRead(x_pin);
    double filtered_acceleration = MovingPointAverage(accelerometer_readings.sum,
                                               accelerometer_readings.reading,
                                               accelerometer_readings.index,
                                               acceleration);
    Serial.println("X Accel: " + String(filtered_acceleration) + " ");
    return filtered_acceleration;
}

// This function updates the velocity global variable and returns the
// new updated value
void UpdateVelocity() {
    // Calculate the time since the last time reading
    float cur_time = millis();
    time_since_last_reading = (cur_time - time);
    time = time_since_last_reading;
    double accel = prev_accel + getXAcceleration();
    velocity += accel * (time_since_last_reading / 1000);
    Serial.println("Velocity: " + String(velocity));
}
