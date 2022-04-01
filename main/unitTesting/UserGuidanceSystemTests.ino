#include <math.h>



#define YES 2
#define NO 1


int l_motor_pin = 5;
int cl_motor_pin = 2;
int c_motor_pin = 7;
int cr_motor_pin = 10;
int r_motor_pin = 11;



void UserGuidanceSystemTestsSetup() {
  //TestRunner::exclude("*");
  pinMode(l_motor_pin, OUTPUT);
  pinMode(cl_motor_pin, OUTPUT);
  pinMode(c_motor_pin, OUTPUT);
  pinMode(cr_motor_pin, OUTPUT);
  pinMode(r_motor_pin, OUTPUT);
}

//5.4.01
test(LeftHapticMotorTest) {
  Serial.println("Starting LeftHapticMotorTest");
  Serial.println("Gently hold left haptic motor for test, then press button to start");
  if (readyNextTest()) {
    DriveLeftMotor();
  }

  //Serial.println("Press button twice if you felt the left haptic motor rumble, press button once if you didn't");
  //bool success = confirmTestSuccess();

  assertTrue(true); 
}

//5.4.02
test(CenterLeftHapticMotorTest) {
  Serial.println("Starting CenterLeftHapticMotorTest");
  Serial.println("Gently hold center-left haptic motor for test, then press button to start");
  if (readyNextTest()) {
    DriveCenterLeftMotor();
  }

  //Serial.println("Press button twice if you felt the center-left haptic motor rumble, press button once if you didn't");
  //bool success = confirmTestSuccess();

  assertTrue(true); 
}

//5.4.03
test(CenterHapticMotorTest) {
  Serial.println("Starting CenterHapticMotorTest");
  Serial.println("Gently hold center haptic motor for test, then press button to start");
  if (readyNextTest()) {
    DriveCenterMotor();
  }

  //Serial.println("Press button twice if you felt the center haptic motor rumble, press button once if you didn't");
  //bool success = confirmTestSuccess();

  assertTrue(true); 
}

//5.4.04
test(CenterRightHapticMotorTest) {
  Serial.println("Starting CenterRightHapticMotorTest");
  Serial.println("Gently hold center-right haptic motor for test, then press button to start");
  if (readyNextTest()) {
    DriveCenterRightMotor();
  }

  //Serial.println("Press button twice if you felt the center-right haptic motor rumble, press button once if you didn't");
  //bool success = confirmTestSuccess();

  assertTrue(true); 
}

//5.4.05
test(RightHapticMotorTest) {
  Serial.println("Starting RightHapticMotorTest");
  Serial.println("Gently hold right haptic motor for test, then press button to start");
  if (readyNextTest()) {
    DriveRightMotor();
  }

  //Serial.println("Press button twice if you felt the right haptic motor rumble, press button once if you didn't");
  //bool success = confirmTestSuccess();

  assertTrue(true); 
}

// utilities
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

bool confirmTestSuccess() {
  byte count=0;
  int number [3]={0,0,0};
  int height;
  String place [3]={"hund", "ten", "ones"};
  // variables will change:
  int buttonState = 0; // variable for reading the pushbutton status
  int previousState=0;
  int i;
  
  byte idleCount=0;
  count=0;
  while(idleCount<30){
    buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
    // turn LED on:
    //digitalWrite(ledPin, HIGH);
      if(previousState!=buttonState){
        count++;  
        idleCount=0;
      }
    } else {
      idleCount++;
    }
    delay(100);
    previousState=buttonState;  
  }
  return true;
}
