// This file contains all of the code pertaining to the guidance system. This
// uses sensor information from ultrasonic sensors, lidar, and accelerometer to
// determine where the user should move to avoid running into an object

// This function determines in which direction there is an obstacle in the path
// of NextStep
void MainGuidance() {
    // Gather the data from the sensor fusion algorithm
    MainSensorFusion();

    // Loop over all of the elements in the distances (global variable)
    /*
    for (int i = 0; i < 5; i++) {
        
    }
    */
}