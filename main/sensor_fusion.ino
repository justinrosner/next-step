// This file contains all of the sensor fusion algorithms used to combine the
// data from the different sensors (ultrasonic sensors, camera, gyro...)

void MainSensorFusion1() {
    // Call to get the data from the ultrasonic sensors and the LIDAR
    MainUltraSensor(); // Ultrasonic distance will now be stores in distances[]

    // TO-DO: Get actual sensor fusion working once we can collect data from
    // lidar. For now we are just going to assume that the filtered ultrasonic
    // data is the fused data.
    for (int i = 0; i < N; i++) {
        fused_distances[i] = distances[i];
    }

    // TO-DO: Remove print statements once fusion system is working
    Serial.println("FUSED LEFT = " + String(fused_distances[0]) + " ");
    Serial.println("FUSED CENTER LEFT = " + String(fused_distances[1]) + " ");
    Serial.println("FUSED CENTER = " + String(fused_distances[2]) + " ");
    Serial.println("FUSED CENTER RIGHT = " + String(fused_distances[3]) + " ");
    Serial.println("FUSED RIGHT = " + String(fused_distances[4]) + " ");
}
