// This file contains all of the code pertaining to the guidance system. This
// uses sensor information from ultrasonic sensors, lidar, and accelerometer to
// determine where the user should move to avoid running into an object. The
// following code implements the "Bubble Rebound Algorithm"

// Header files to include for the guidance system
#include <math.h>

// Constants used in the "Bubble Rebound Algorithm"
double bubble_boundary[N];
double ki = 0.8; // This is a scaling constant. Try values between [0.2-3]
double a_0 = M_PI / N;

// This function updates the bubble_boundary array
void UpdateBubbleBoundary() {
    // Update the velocity
    // TO-DO: Uncomment this when the accelerometer is setup
    //UpdateVelocity();
    velocity = 100.0; // temp value for velocity (measure in cm/s)

    for (int i = 0; i < N; i++) {
        // Update the bubble_boundary value
        bubble_boundary[i] = ki * velocity;
    }
}

// This function performs a basic check to see if there is an obstacle in the
// bubble
bool CheckForObstacles() {
    for (int i = 0; i < N; i++) {
        if (fused_distances[i] <= bubble_boundary[i]) {
            return true;
        } else {return false;}
    }
}

// This function computes the rebound angle. The rebound angle is the direction
// in which we will now be travelling to avoid running into the obstacle.
float ComputeReboundAngle() {
    // TO-DO: FIGURE OUT WHY THIS IS NOT WORKING
    double numerator = 0;
    double denominator = 0;
    
    // Go over the left sensors
    for (int i = -2; i < 0; i++) {
        double a_i_left = (i - 1) * a_0;
        numerator += a_i_left * fused_distances[i + 2];
        denominator += fused_distances[i + 2];
    }

    // Go over the middle and right sensors
    for (int i = 0; i < 3; i++) {
        double a_i_right = (i + 1) * a_0;
        //Serial.println("numerator = " + String(a_i_right * fused_distances[i + 2]) + " :" + String(i+1) + " ");
        numerator += a_i_right * fused_distances[i + 2];
        denominator += fused_distances[i + 2];
    }

    return numerator / denominator;
}

// This function calculates what sector to indicate (with the haptic motors)
// based off of the rebound angle. The first sector is the one which the right
// sensor covers and as the sectors increase they move across the sensors until
// you get to the last sector (the left ultrasonic sensor)
int CalculateSector(float rebound_angle) {
    // Falls in the first sector (where the right sensor is)
    if (rebound_angle <= 36) {
        // TO-DO: We need to make the signals here for what haptic motors to
        //        signal to
    } else if (rebound_angle <= 72) {
        // Falls in the second sector
    } else if (rebound_angle <= 108) {
        // Falls in the third sector
    } else if (rebound_angle <= 144) {
        // Falls in the fourth sector
    } else if (rebound_angle <= 180) {
        // Falls in the fifth sector
    } else {
        // No available options at the current moment, have the user turn around

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
        Serial.println("new_direction = " + String(new_direction) + " ");
    } else {
        // No obstacle found, keep moving straight (no guidance needed)
        return;
    }
}