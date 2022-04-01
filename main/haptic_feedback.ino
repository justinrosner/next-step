// This file contains all of the code related to triggering the haptic motors

// Pin Mapping
// TO-DO: We need to figure out what values we are going to put in here for the
// new board
int l_motor_pin = 5;
int cl_motor_pin = 2;
int c_motor_pin = 7;
int cr_motor_pin = 10;
int r_motor_pin = 11;

void HapticMotorSetup() {
    pinMode(l_motor_pin, OUTPUT);
    pinMode(cl_motor_pin, OUTPUT);
    pinMode(c_motor_pin, OUTPUT);
    pinMode(cr_motor_pin, OUTPUT);
    pinMode(r_motor_pin, OUTPUT);
}

void DriveLeftMotor() {
    digitalWrite(l_motor_pin, HIGH); //vibrate
    delay(500);                     // delay half a second
    digitalWrite(l_motor_pin, LOW);  //stop vibrating 
}

void DriveCenterLeftMotor() {
    digitalWrite(cl_motor_pin, HIGH); //vibrate
    delay(500);                       // delay half a second
    digitalWrite(cl_motor_pin, LOW);  //stop vibrating
}

void DriveCenterMotor() {
    digitalWrite(c_motor_pin, HIGH); //vibrate
    delay(500);                      // delay half a second
    digitalWrite(c_motor_pin, LOW);  //stop vibrating
}

void DriveCenterRightMotor() {
    digitalWrite(cr_motor_pin, HIGH); //vibrate
    delay(500);                       // delay half a second
    digitalWrite(cr_motor_pin, LOW);  //stop vibrating
}

void DriveRightMotor() {
    digitalWrite(r_motor_pin, HIGH); //vibrate
    delay(500);                      // delay half a second
    digitalWrite(r_motor_pin, LOW);  //stop vibrating
}
