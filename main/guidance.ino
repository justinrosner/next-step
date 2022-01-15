// This file contains all of the code pertaining to the guidance system. This
// uses sensor information from ultrasonic sensors, lidar, and accelerometer to
// determine where the user should move to avoid running into an object. The
// following code implements the "Bubble Rebound Algorithm"

// Header files to include for the guidance system
#include <math.h>

// Constants used in the "Bubble Rebound Algorithm"
double bubble_boundary[N];
double ki = 0.8;  // This is a scaling constant. Try values between [0.2-3]
double alpha_0 = M_PI / N;

// This function updates the bubble_boundary array
void UpdateBubbleBoundary() {
  // Update the velocity
  // TO-DO: Uncomment this when the accelerometer is setup
  // UpdateVelocity();
  velocity = 100.0;  // temp value for velocity (measure in cm/s)

  for (int i = 0; i < N; i++) {
    // Update the bubble_boundary value
    bubble_boundary[i] = ki * velocity;
  }
}

// This function performs a basic check to see if there is an obstacle in the
// bubble
bool CheckForObstacles() {
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

// This function computes the rebound angle. The rebound angle is the direction
// in which we will now be travelling to avoid running into the obstacle.
float ComputeReboundAngle() {
  double numerator = 0;
  double denominator = 0;

  // Loop to calculate the numerator and denominator
  for (int i = 0; i < N; i++) {
    double alpha_i = (i + 1) * alpha_0;
    numerator += alpha_i * fused_distances[i];
    denominator += fused_distances[i];
  }

  return numerator / denominator;
}

// This function calculates what sector to indicate (with the haptic motors)
// based off of the rebound angle. The first sector is the one which the right
// sensor covers and as the sectors increase they move across the sensors until
// you get to the last sector (the left ultrasonic sensor)
int CalculateSector(float rebound_angle) {
  Serial.println("Rebound Angle = " + String(rebound_angle) + " ");
  // Falls in the first sector (where the left sensor is)
  if (rebound_angle >= 0 && rebound_angle < 0.62) {
    Serial.println("LEFT BUZZER");
  } else if (rebound_angle >= 0.62 && rebound_angle < 1.25) {
    // Falls in the second sector
    Serial.println("CENTER LEFT BUZZER");
  } else if (rebound_angle >= 1.25 && rebound_angle < 1.88) {
    // Falls in the third sector
    Serial.println("CENTER BUZZER");
  } else if (rebound_angle >= 1.88 && rebound_angle < 2.51) {
    // Falls in the fourth sector
    Serial.println("CENTER RIGHT BUZZER");
  } else if (rebound_angle >= 2.51 && rebound_angle < 3.14) {
    // Falls in the fifth sector (Where the right sensor is)
    Serial.println("RIGHT BUZZER");
  } else {
    // Otherwise there are no free moves that can be made and the user
    // should be instructed to turn around
  }
}

// Main function that implements the "Bubble Rebound Algorithm"
void MainGuidance() {
  // Gather the data from the sensor fusion algorithm
  MainSensorFusion();

  // Update the Bubble Boundary
  UpdateBubbleBoundary();

  // Check if there is an obstacle in the bubble
  if (CheckForObstacles()) {
    // Obstacle found, compute new heading
    float new_direction = ComputeReboundAngle();
    CalculateSector(new_direction);
  } else {
    // No obstacle found, keep moving straight (no guidance needed)
    return;
  }
}