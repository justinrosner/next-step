// This file contains all of the code relating to gathering velocity data from
// the accelerometer

// Pin Assignments
// TO-DO: Assign the proper pins after we get the wiring done
int ground_pin = 0;
int power_pin = 0;
// These need to be assigned to analog pins
int x_pin = A0;
int y_pin = A1;
int z_pin = A2;

// This function handles the setup of the accelerometer
void AccelerometerSetup() {
    pinMode(ground_pin, OUTPUT);
    pinMode(power_pin, OUTPUT);
    digitalWrite(ground_pin, LOW);
    digitalWrite(power_pin, HIGH);
}

// This is a helper function to get the acceleration in the x direction
double getXAcceleration() {
    Serial.println("X Accel: " + String(analogRead(x_pin)) + " ");
    return analogRead(x_pin);
}

// This function updates the velocity global variable and returns the
// new updated value
void UpdateVelocity() {
    // Calculate the time since the last time reading
    float cur_time = millis();
    time_since_last_reading = cur_time - time;
    velocity = velocity + getXAcceleration() * time_since_last_reading;
}
