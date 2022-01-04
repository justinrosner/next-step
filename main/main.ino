int trigPin = 7;
int echoPin = 5;
int trigPin2 = 4;
int echoPin2 = 3;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  Serial.begin(9600);
}

void loop() { MainUltraSensor(); }
