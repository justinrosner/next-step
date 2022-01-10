// This file contains all of the functions related to the setup and collection
// of data from the ultrasonic sensors

int cl_echo = 2;
int cl_trig = 3;
int c_echo = 4;
int c_trig = 5;
int cr_echo = 6;
int cr_trig = 7;
int r_echo = 8;
int r_trig = 9;
int l_echo = 10;
int l_trig = 11;

int Ultra(int trig, int echo) {
  // Clears the trigPin
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(echo, HIGH);

  // Calculating and returning the distance
  return (duration * 0.0343 / 2);
}

void UltraSetup() {
  pinMode(cl_trig, OUTPUT);
  pinMode(cl_echo, INPUT);
  pinMode(c_trig, OUTPUT);
  pinMode(c_echo, INPUT);
  pinMode(cr_trig, OUTPUT);
  pinMode(cr_echo, INPUT);
  pinMode(r_trig, OUTPUT);
  pinMode(r_echo, INPUT);
  pinMode(l_trig, OUTPUT);
  pinMode(l_echo, INPUT);
}

void MainUltraSensor() {
  // Calculate and store the distances from each sensor
  int cl_d = Ultra(cl_trig, cl_echo);
  distances[1] = cl_d;
  delayMicroseconds(2);
  int c_d = Ultra(c_trig, c_echo);
  distances[2] = c_d;
  delayMicroseconds(2);
  int cr_d = Ultra(cr_trig, cr_echo);
  distances[3] = cr_d;
  delayMicroseconds(2);
  int r_d = Ultra(r_trig, r_echo);
  distances[4] = r_d;
  delayMicroseconds(2);
  int l_d = Ultra(l_trig, l_echo);
  distances[0] = l_d;

  // Print out the data from the sensors
  Serial.println("CENTER LEFT = " + String(cl_d) + " ");
  Serial.println("CENTER = " + String(c_d) + " ");
  Serial.println("CENTER RIGHT = " + String(cr_d) + " ");
  Serial.println("RIGHT = " + String(r_d) + " ");
  Serial.println("LEFT = " + String(l_d) + " ");
}
