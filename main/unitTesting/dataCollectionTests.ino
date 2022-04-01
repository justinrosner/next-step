

int const len=5;
int errorMarginUS = 5;
int threshold = 5;
int thresholdAngle = 5;

struct scannedPoint{
    float distance;
    float angle;
    bool operator>(const scannedPoint& rhs) const {
        return this->angle > rhs.angle;
    }
    bool operator<(const scannedPoint& rhs) const {
        return this->angle < rhs.angle;
    }
};

//UltraSonic s [len];


int trig [len];
int echo [len];

// Unit testing for Data collection suite: Ultrasonic Sensors

void dataCollectionTestsSetup() {
  
  
  
  
  //TestRunner::include("UltrasonicSensorReadingTest15cm*");

  TestRunner::setTimeout(10000);
  //s[0]=UltraSonic(28, 29, 15, 12.6, 10, 0.0001, 0.999, 72);//right
  //s[1]=UltraSonic(26, 27, 15, 12.6, 10, 0.0001, 0.999, 36); //centerright
  //s[2]=UltraSonic(24, 25, 15, 12.6, 10, 0.0001, 0.999, 0); //center
  //s[3]=UltraSonic(22, 23, 15, 12.6, 10, 0.0001, 0.999, 324); //centerleft
  //s[4]=UltraSonic(30, 31, 15, 12.6, 10, 0.0001, 0.999, 288); //left

  
  trig[0] = 22;
  trig[1] = 24;
  trig[2] = 26;
  trig[3] = 28;
  trig[4] = 30;
  
  echo[0] = 23;
  echo[1] = 25;
  echo[2] = 27;
  echo[3] = 29;
  echo[4] = 31;
  pinMode(trig[0], OUTPUT);
  pinMode(echo[0], INPUT);
  pinMode(trig[1], OUTPUT);
  pinMode(echo[1], INPUT);
  pinMode(trig[2], OUTPUT);
  pinMode(echo[2], INPUT);
  pinMode(trig[3], OUTPUT);
  pinMode(echo[3], INPUT);
  pinMode(trig[4], OUTPUT);
  pinMode(echo[4], INPUT);
  
}


// Test: 5.2.01
test(UltrasonicSensorReadingTest15cm) {
  // Object placed 15cm from sensor
  Serial.println("Starting UltrasonicSensorReadingTest15cm");
  for (int i = 0; i < len; i++){
    int dist = 0;
    int res = 6;
    int counter = 0;
    Serial.println("trigger: " + String(trig[i]) + ", echo: " + String(echo[i]));
    Serial.println("Press Button when ready to begin");
    if (readyNextTest()) {
      while (abs(dist - 15) >= errorMarginUS && counter <= 30000) {
        Serial.println("US distance " + String(dist));
        dist = getDistanceFromSensor(i);
        res = abs(dist-15);
        counter++;
      }
      Serial.println("Final Distance: " + String(dist) + ", margin of error: " + String(res));
      assertLessOrEqual(res, errorMarginUS);
    } 
  }  
}

// Test: 5.2.02
test(UltrasonicSensorReadingTest150cm) {
  // Object placed 150cm from sensor
  Serial.println("Starting UltrasonicSensorReadingTest150cm");
  for (int i = 0; i < len; i++){
    int dist = 0;
    int res = 6;
    int counter = 0;
    Serial.println("trigger: " + String(trig[i]) + ", echo: " + String(echo[i]));
    Serial.println("Press Button when ready to begin");
    if (readyNextTest()) {
      while (abs(dist - 150) >= errorMarginUS && counter <= 1000) {
        Serial.println("US distance " + String(dist));
        dist = getDistanceFromSensor(i);
        res = abs(dist-150);
        counter++;
      }
      Serial.println("Final Distance: " + String(dist) + ", margin of error: " + String(res));
      assertLessOrEqual(res, errorMarginUS);
    } 
  }
}

// Test: 5.2.03
test(UltrasonicSensorReadingTest500cm) {
  // Object placed 500cm from sensor
  Serial.println("Starting UltrasonicSensorReadingTest500cm");
  for (int i = 0; i < len; i++){
    int dist = 0;
    int res = 6;
    int counter = 0;
    Serial.println("trigger: " + String(trig[i]) + ", echo: " + String(echo[i]));
    Serial.println("Press Button when ready to begin");
    if (readyNextTest()) {
      while (abs(dist - 500) >= errorMarginUS && counter <= 1000) {
        Serial.println("US distance " + String(dist));
        dist = getDistanceFromSensor(i);
        res = abs(dist-500);
        counter++;
      }
      Serial.println("Final Distance: " + String(dist) + ", margin of error: " + String(res));
      assertLessOrEqual(res, errorMarginUS);
    } 
  }  
}


// Test: 5.2.04
test(LidarReadingTest30cm) {
  // Object placed 150cm from sensor
  Serial.println("Starting LidarReadingTest30cm: Set object at distance 30cm, angle: 30deg from left");
  Serial.println("Press Button when ready to begin");
  if (readyNextTest()) {
    for (int i = 0; i < sizeof(L.points); i++) {
      if (abs(L.points[i].angle - 300) <= thresholdAngle) {
        int res = abs(L.points[i].distance - 30);
        assertLessOrEqual(res, threshold);
      }
    }
  }
}

// Test: 5.2.05
test(LidarReadingTest100cm) {
  // Object placed 150cm from sensor
  Serial.println("Starting LidarReadingTest150cm: Set object at distance 100cm, angle: 50deg from left");
  Serial.println("Press Button when ready to begin");
  if (readyNextTest()) {
    for (int i = 0; i < sizeof(L.points); i++) {
      if (abs(L.points[i].angle - 320) <= thresholdAngle) {
        int res = abs(L.points[i].distance - 100);
        assertLessOrEqual(res, threshold);
      }
    }
  }
}

// Test: 5.2.06
test(LidarReadingTest300cm) {
  // Object placed 150cm from sensor
  Serial.println("Starting LidarReadingTest300cm: Set object at distance 300cm, angle: 90deg from left");
  Serial.println("Press Button when ready to begin");
  if (readyNextTest()) {
    for (int i = 0; i < sizeof(L.points); i++) {
      if (abs(L.points[i].angle - 360) <= thresholdAngle) {
        int res = abs(L.points[i].distance - 300);
        assertLessOrEqual(res, threshold);
      }
    }
  }
}

// Test: 5.2.07
//test(LidarReadingTest600cm) {
//  // Object placed 150cm from sensor
//  Serial.println("Starting LidarReadingTest600cm: Set object at distance 600cm, angle: 120deg from left");
//  Serial.println("Press Button when ready to begin");
//  if (readyNextTest()) {
//    
//    for (int i = 0; i < sizeof(L.points); i++) {
//      if (abs(L.points[i].angle - 30) <= thresholdAngle) {
//        int res = abs(L.points[i].distance - 600);
//       assertLessOrEqual(res, threshold);
//      }
//    }
//  }
//}

// Test: 5.2.08
//test(LidarReadingTest1000cm) {
  // Object placed 150cm from sensor
//  Serial.println("Starting LidarReadingTest1000cm: Set object at distance 1000cm, angle: 180deg from left");
//  Serial.println("Press Button when ready to begin");
//  Lidar::scannedPoint points[L.pointInd] = L.points;
//  if (readyNextTest()) {
//    for (int i = 0; i < sizeof(L.points); i++) {
//      Serial.println("distance LiDAR: " + String(L.points[i].distance) + ", angle: " + String(L.points[i].angle));
//      if (abs(L.points[i].angle - 90) <= thresholdAngle) {
//        int res = abs(L.points[i].distance - 1000);
//        assertLessOrEqual(res, threshold);
//      }
//    }
//  }
//}



float getDistanceFromSensor(int sensorId) {
    digitalWrite(trig[sensorId], LOW);
    delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig[sensorId], HIGH);
    delayMicroseconds(10);
    digitalWrite(trig[sensorId], LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
    float duration = pulseIn(echo[sensorId], HIGH);


    float distanceUS= duration*0.0343/2;

    return distanceUS;
}
