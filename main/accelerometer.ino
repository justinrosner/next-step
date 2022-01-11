// This file contains all of the code relating to gathering velocity data from
// the accelerometer

// Pin Assignments
// TO-DO: Assign the proper pins after we get the wiring done
int ground_pin = 0;
int power_pin = 0;
// These need to be assigned to analog pins
int x_pin = A3;
int y_pin = A2;
int z_pin = A1;

// This function handles the setup of the accelerometer
void AccelerometerSetup() {
    pinMode(ground_pin, OUTPUT);
    pinMode(power_pin, OUTPUT);
    digitalWrite(ground_pin, LOW);
    digitalWrite(power_pin, HIGH);
}

// This is a helper function to get the acceleration in the x direction
double getXAcceleration() {
    return analogRead(x_pin);
}

// This function updates the velocity global variable and returns the
// new updated value
double getVelocity() {
    // Calculate the time since the last time reading
    float cur_time = millis();
    float t = cur_time - time;
    velocity = velocity + getXAcceleration() * t;
    return velocity;
}
