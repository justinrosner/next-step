int trigPin = 7;
int echoPin = 5;
int trigPin2 = 4;
int echoPin2 = 3;

void setup() {
  UltraSetup();
  Serial.begin(9600);
}

void loop() { 
  MainUltraSensor();
}
