// Main file

// Import
#include "system_diagnostic.h"

// Global Declarations used across files
#define N 5
double distances[N];          // Ultrasonic distances
double fused_distances[N];    // fused distance points for each of the 5 sectors
double velocity = 0.0;          // Velocity of user (assumed to be forwards)
double time = millis();
double time_since_last_reading = 0.0;
SystemDiagnostic diagnosticModule;

void setup() {
  Serial.begin(9600);
  ButtonSetup();
  UltraSetup();
  diagnosticModule = *(new SystemDiagnostic());
  GetUserHeight();
}

void loop() {
  MainGuidance();
}
