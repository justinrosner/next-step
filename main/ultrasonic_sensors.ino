// This file contains all of the functions related to the setup and collection
// of data from the ultrasonic sensors

// Constants for moving point average
#define WINDOW_SIZE 20

// Define a struct to store the information needed for Moving Point Average
struct SensorInformation {
  int index = 0;
  double sum = 0;
  double reading[WINDOW_SIZE];
};

// Create an array of SensorInformation structs
struct SensorInformation sensors[N];

// Pin assignments
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

// This function calculates the raw unfiltered distance data from the sensors
double Ultra(int trig, int echo) {
  // Clears the trigPin
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  double duration = pulseIn(echo, HIGH);

  // Calculating and returning the distance
  return (duration * 0.0343 / 2);
}

// This function is to be called in the main setup function and performs all of
// the pin assignments for the ultrasonic sensors
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

// This function performs a simple moving point average on the data from the
// sensors to 
double MovingPointAverage(double &sum, double readings[], int &index,
                          double &val) {
  sum = sum - readings[index];
  readings[index] = val;
  sum = sum + val;
  index = (index + 1) % WINDOW_SIZE;
  return (sum / WINDOW_SIZE);
}

// This is the main function that is to be called by other files that wish to
// use the ultrasonic sensors
void MainUltraSensor() {
  // Calculate and store the distances from each sensor
  double l_d = Ultra(l_trig, l_echo);
  distances[0] = MovingPointAverage(sensors[0].sum, sensors[0].reading,
                                    sensors[0].index, l_d);
  delayMicroseconds(2);
  double cl_d = Ultra(cl_trig, cl_echo);
  distances[1] = MovingPointAverage(sensors[1].sum, sensors[1].reading,
                                    sensors[1].index, cl_d);
  delayMicroseconds(2);
  double c_d = Ultra(c_trig, c_echo);
  distances[2] = MovingPointAverage(sensors[2].sum, sensors[2].reading,
                                    sensors[2].index, c_d);
  delayMicroseconds(2);
  double cr_d = Ultra(cr_trig, cr_echo);
  distances[3] = MovingPointAverage(sensors[3].sum, sensors[3].reading,
                                    sensors[3].index, cr_d);
  delayMicroseconds(2);
  double r_d = Ultra(r_trig, r_echo);
  distances[4] = MovingPointAverage(sensors[4].sum, sensors[4].reading,
                                    sensors[4].index, r_d);
}
