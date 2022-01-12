// This file contains all of the sensor fusion algorithms used to combine the
// data from the different sensors (ultrasonic sensors, camera, gyro...)

// This function performs Kalman filtering on the ultrasonic sensor data and
// lidar data to 
void KalmanFilter() {

}

void MainSensorFusion() {
    // Call to get the data from the ultrasonic sensors and the LIDAR
    MainLidar();
    MainUltraSensor(); // Ultrasonic distance will now be stores in distances[]

    // TO-DO: Remove this once you get the basic guidance system working
    //Serial.println("FILTERED LEFT = " + String(distances[0]) + " ");
    //Serial.println("FILTERED CENTER LEFT = " + String(distances[1]) + " ");
    //Serial.println("FILTERED CENTER = " + String(distances[2]) + " ");
    //Serial.println("FILTERED CENTER RIGHT = " + String(distances[3]) + " ");
    //Serial.println("FILTERED RIGHT = " + String(distances[4]) + " ");

    // TO-DO: Get actual sensor fusion working once we can collect data from
    // lidar. For now we are just going to assume that the filtered ultrasonic
    // data is the fused data.
    for (int i = 0; i < N; i++) {
        fused_distances[i] = distances[5];
    }
}