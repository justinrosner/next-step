// Main file

// Global Declarations used across files
#define N 5
double distances[N];          // Ultrasonic distances
double fused_distances[N];    // fused distance points for each of the 5 sectors
double velocity = 0.0;          // Velocity of user (assumed to be forwards)
double time = millis();
double time_since_last_reading = 0.0;

void setup() {
  Serial.begin(9600);
  AccelerometerSetup();
  UltraSetup();
}

void loop() { 
  MainGuidance();
}
