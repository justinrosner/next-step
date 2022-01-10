// This file contains all of the sensor fusion algorithms used to combine the
// data from the different sensors (ultrasonic sensors, camera, gyro...)

void MainSensorFusion() {
    // Call to get the data from the ultrasonic sensors and the LIDAR
    MainLidar();
    MainUltraSensor();

    
}