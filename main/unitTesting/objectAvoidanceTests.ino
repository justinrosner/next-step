#include <math.h>

const int N = 5;
double bubble_boundary[N];
const double ki = 2.5; //scaling constant for bubble boundary
const double alpha_0 = M_PI / N; //Used to define each sector

double velocity = 100;



void objectAvoidanceTestsSetup() {
  velocity = 100.0;
  UpdateBubbleBoundary();
}


// 5.3.01
test(ReboundAngleCalculationTest){
  // grab fused distances from sensor fusion
  Serial.println("Starting ReboundAngleCalculationTest: input = [1200, 200, 100, 1200, 1200]");
  double fused_distances[5] = {1200, 200, 100, 1200, 1200};
  float rebound_angle = ComputeReboundAngle(fused_distances);

  Serial.println("Calculated rebound angle: " + String(rebound_angle) + ", Expected rebound angle: 1.99");

  float res = abs(1.99 - rebound_angle);
  assertLessOrEqual(res, 0.01); 
}

//5.3.02
test(NoObjectPresentTest) {
  Serial.println("Starting NoObjectPresentTest: input = [1200, 1200, 1200, 1200, 1200]");

  double fused_distances[5] = {1200, 1200, 1200, 1200, 1200};
  bool obstacleFlag = CheckForObstacles(fused_distances);
  Serial.println("Obstacles within bubble boundary? " + String(obstacleFlag) + ", expected: false");
  assertFalse(obstacleFlag);
}

//5.3.03
test(NearingWallTest) {
  Serial.println("Starting NearingWallTest: input = [1200, 200, 200, 200, 1200]");

  double fused_distances[5] = {1200, 200, 200, 200, 1200};
  float rebound_angle = ComputeReboundAngle(fused_distances);

  Serial.println("Calculated rebound angle: " + String(rebound_angle) + ", Expected rebound angle: 1.88, rebound sector: center-right");

  float res = abs(1.88 - rebound_angle);
  assertLessOrEqual(res, 0.01);

}

//5.3.04
test(UpdatingBubbleBoundaryChangingSpeed){
  Serial.println("Starting UpdatingBubbleBoundaryChangingSpeed: current velocity = 1m/s, change to 1.2m/s, expected boundary is now 500cm");
  velocity = 200.0;
  double bound = 500.0;
  UpdateBubbleBoundary();
  

  for (int i = 0; i < N; i++){
    assertEqual(bubble_boundary[i], bound);
  }
  velocity = 100.0;
  UpdateBubbleBoundary();
}

//5.3.05
test(UpdatingBubbleBoundaryStandingStill){
  Serial.println("Starting UpdatingBubbleBoundaryChangingSpeed: current velocity = 1m/s, change to 0m/s, expected boundary is now 250cm");
  velocity = 0;
  double bound = 250.0;
  UpdateBubbleBoundary();
  

  for (int i = 0; i < N; i++){
    assertEqual(bubble_boundary[i], bound);
  }
  velocity = 100.0;
  UpdateBubbleBoundary();
}

//5.3.06
test(UpdatingBubbleBoundaryMaximalSpeed){
  Serial.println("Starting UpdatingBubbleBoundaryChangingSpeed: current velocity = 1m/s, change to 0m/s, expected boundary is now 500");
  velocity = 0;
  double bound = 250.0;
  UpdateBubbleBoundary();
  

  for (int i = 0; i < N; i++){
    assertEqual(bubble_boundary[i], bound);
  }
  velocity = 100.0;
  UpdateBubbleBoundary();
}

// Modified Standalone code for testing

float ComputeReboundAngle(double fused_distances[]) {
  double numerator = 0;
  double denominator = 0;

  // Loop to calculate the numerator and denominator
  for (int i = 0; i < N; i++) {
    double alpha_i = (i + 1) * alpha_0;
    //Serial.println(String(fused_distances[i])+ " " + String(i));
    numerator += alpha_i * fused_distances[i];
    denominator += fused_distances[i];
  }

  return numerator / denominator;
}


bool CheckForObstacles(double fused_distances[]) {
  int count = 0;
  for (int i = 0; i < N; i++) {
    if (fused_distances[i] <= bubble_boundary[i])
      count++;
  }

  // If none of the sensors have detected an object we return false
  if (count == 0) {
    return false;
  }
  // Otherwise it means that the sensors have detected an object and
  // we return true
  return true;
}

void UpdateBubbleBoundary() {
  // Use default velocity in cm/s
  double value = 0.0;
  
  // If the velocity is less than 1m/s then we want to use a fixed bubble
  // boundary size
  if (velocity <= 100.0) {
    value = 100.0;
  } else {
    value = velocity;
  }
  
  //Serial.println("Bubble Boundary: " + String(ki * value));

  for (int i = 0; i < N; i++) {
    // Update the bubble_boundary value
    bubble_boundary[i] = ki * value;
  }

}

int CalculateSector(float rebound_angle) {
  Serial.println("Rebound Angle = " + String(rebound_angle) + " ");
  // Falls in the first sector (where the left sensor is)
  if (rebound_angle >= 0 && rebound_angle < 0.62) {
    Serial.println("LEFT BUZZER");
    //DriveLeftMotor();
  } else if (rebound_angle >= 0.62 && rebound_angle < 1.25) {
    // Falls in the second sector
    Serial.println("CENTER LEFT BUZZER");
    //DriveCenterLeftMotor();
  } else if (rebound_angle >= 1.25 && rebound_angle < 1.88) {
    // Falls in the third sector
    Serial.println("CENTER BUZZER");
    //DriveCenterMotor();
  } else if (rebound_angle >= 1.88 && rebound_angle < 2.51) {
    // Falls in the fourth sector
    Serial.println("CENTER RIGHT BUZZER");
    //DriveCenterRightMotor();
  } else if (rebound_angle >= 2.51 && rebound_angle < 3.14) {
    // Falls in the fifth sector (Where the right sensor is)
    Serial.println("RIGHT BUZZER");
    //DriveRightMotor();
  } else {
    // Otherwise there are no free moves that can be made and the user
    // should be instructed to turn around
  }
}
