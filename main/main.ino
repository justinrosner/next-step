// Main file

// Global Declarations used across files
int distances[5];

void setup() {
  Serial.begin(9600);
  UltraSetup();
}

void loop() { 
  MainGuidance();
}
