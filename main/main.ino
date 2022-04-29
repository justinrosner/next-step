// Main file

// Import
#include "system_diagnostic.h"

// Global Declarations used across files
#define N 5
double distances[N];          // Ultrasonic distances
double fused_distances[N];    // fused distance points for each of the 5 sectors
float velocity = 0.0;          // Velocity of user (assumed to be forwards)
int height;
double time = millis();
SystemDiagnostic diagnosticModule;

void setup() {
  Serial.begin(9600);
  ButtonSetup();
  accelSetup();
  fusionSetup();
  SDCardSetup();
  diagnosticModule = *(new SystemDiagnostic());
  
  // Check if the user has already entered a height in a previous use of the
  // device. If it already exists then we can just read the value as is
  if (CheckIfFileExists("UserHeight.txt")) {
    height = ReadHeightFromSD();
  } else {
    // Otherwise we have to run the PushButton module to get the user input
    GetUserHeight();
  }

  Serial.println("Finished Setup");
}

void loop() {
  MainGuidance();
}
