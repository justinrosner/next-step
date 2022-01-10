// This file contains all of the functions related to the setup and collection
// of data from the ultrasonic sensors

int echo1 = 2;
int trig1 = 3;
int echo2 = 4;
int trig2 = 5;
int echo3 = 6;
int trig3 = 7;
int echo4 = 8;
int trig4 = 9;
int echo5 = 10;
int trig5 = 11;

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
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  
  // Uncomment when all 5 sensors are up and working
  /*
  pinMode(trig4, OUTPUT);
  pinMode(echo4, INPUT);
  pinMode(trig5, OUTPUT);
  pinMode(echo5, INPUT);
  */
}

void MainUltraSensor() {
  int d1 = Ultra(trig1, echo1);
  delayMicroseconds(2);
  int d2 = Ultra(trig2, echo2);
  delayMicroseconds(2);
  int d3 = Ultra(trig3, echo3);
  
  // Uncomment this when all 5 sensors are up and working
  /*
  delayMicroseconds(2);
  int d4 = Ultra(trig4, echo4);
  delayMicroseconds(2);
  int d5 = Ultra(trig5, echo5);
  */

  Serial.println("distance1 = " + String(d1) + " ");
  Serial.println("distance2 = " + String(d2) + " ");
  Serial.println("distance3 = " + String(d3) + " ");
}

// All of the old code that we used for the POC demo is below here
/*
#define SIZE 20
int n = 2;
int index = 0;
int value = 0;
int sum = 0;
int samples[SIZE];
int avg = 0;
int index2 = 0;
int value2 = 0;
int sum2 = 0;
int samples2[SIZE];
int avg2 = 0;
float Raw[2];
float Position[2] = {0, 13};
float Calc_X[1];
float Calc_Y[1];
int test[1];
float Final_X, Final_Y;
int distance;
int dist;
int duration;
float e_mea = 0.01;
float e_est = 0.01;
float q = 0.001;
int distance2;
int duration2;

// This function combines data of various sensor data combination with
// weightage as per accuracy of perticular combination
// and proportional to distance in between sensors
void FuseData() {
  float temp_sum = 0;
  int count = 0;
  Final_X = 0;
  Final_Y = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (test[count] == 1) {
        temp_sum = temp_sum + Position[j] - Position[i];
      }

      Final_X =
          Final_X + Calc_X[count] * test[count] * (Position[j] - Position[i]);
      Final_Y =
          Final_Y + Calc_Y[count] * test[count] * (Position[j] - Position[i]);

      count = count + 1;
    }
  }

  Final_X = Final_X / temp_sum;
  Final_Y = Final_Y / temp_sum;
}

// This function calculates the position of an object
void PositionCalc() {
  float d1, d2, a;
  int count, test_temp;
  count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      d1 = Raw[i];
      d2 = Raw[j];
      a = (Position[j] - Position[i]);
      test_temp = check(d1, d2, a);
      // Serial.println(test_temp);
      // test_temp=1;
      if (test_temp == 0) {
        Calc_X[count] = 0;
        Calc_Y[count] = 0;
        test[count] = 0;
      }

      if (test_temp == 1) {
        //  Serial.print(d1);Serial.print("\t");
        //  Serial.print(d2);Serial.print("\t");
        //  Serial.print(a);Serial.print("\t");

        // applying cosine rule to calculate angle
        float theta = acos((((d1 * d1) + (a * a) - (d2 * d2))) / (2 * d1 * a));
        Calc_X[count] = d1 * cos(theta) + Position[i];  // y coordinate
        Calc_Y[count] = d1 * sin(theta);                // X coordinate
        test[count] = 1;
        //   Serial.print(Position[i]);Serial.print("\t");
      }
      // Serial.print(Calc_X[count]);Serial.print("\t");
      // Serial.print(Calc_Y[count]);Serial.print("\t");
      // Serial.print(test[count]);Serial.print("\n");

      count = count + 1;
    }
  }
}

void Ultra() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // float estimated_x = kf.updateEstimate(duration);

  // Calculating the distance
  distance = duration * 0.0343 / 2;
  // dist = estimated_x*0.034/2;
}

void Ultra2() {
  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);

  // Calculating the distance
  distance2 = duration2 * 0.0343 / 2;
}

// This function handles the calling of functions needed to properly gather
// data from the Ultra Sonic Sensors
void MainUltraSensor() {
  Ultra();
  delayMicroseconds(2);
  Ultra2();
  // Serial.println("distance = " + String(distance) + " ");
  // Serial.println("distance2 = " + String(distance2) + " ");
  sum = sum - samples[index];
  sum2 = sum2 - samples2[index2];

  value = distance;
  value2 = distance2;

  samples[index] = value;
  samples2[index2] = value2;

  sum += value;
  sum2 += value2;

  index = (index + 1) % SIZE;
  index2 = (index2 + 1) % SIZE;

  avg = sum / SIZE;
  avg2 = sum2 / SIZE;
  // Serial.println("avg = " + String(avg) + " ");
  // Serial.println("avg2 = " + String(avg2) + " ");

  Raw[0] = avg;
  Raw[1] = avg2;
  // Raw[0]=distance;
  // Raw[1]=distance2;
  PositionCalc();
  FuseData();
  Serial.print("finalx: " + String(Final_X));  // X coordinate
  Serial.print("\t");
  Serial.println("finaly: " + String(Final_Y));

  delay(5);

  // Serial.println("distance = " + String(distance) + " ");
  // Serial.println("distanceFilt = " + String(dist) + " ");
  // Serial.println("distanceFilt = " + String(avg) + " ");
  // Serial.println("distance = " + String(abs(avg2-avg)) + " ");
}
*/