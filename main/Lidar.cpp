#include "Lidar.h"
Lidar::Lidar(){}
Lidar::Lidar(float meaErr, float estErr, float r, float d, float variance, int tx, int rx){
	filt.setVar(meaErr, estErr);
	var=variance;
	range=r;
	depressAngle=d;
	//set pins tx and ar and motor contr
	lidar.begin(Serial1);
	pinMode(RPLIDAR_MOTOR, OUTPUT);
}

Lidar::~Lidar(){
	//end();
	return;
}

float Lidar::getCenter(){
	return direction;
}

float Lidar::sensorLoop(){
	if (IS_OK(lidar.waitPoint())) {

		float distance = lidar.getCurrentPoint().distance;         // distance value in mm unit
   		float angle = lidar.getCurrentPoint().angle;  // anglue value in degree
    		bool startBit = lidar.getCurrentPoint().startBit;  // whether this point is belong to a new scan
    		byte quality =lidar.getCurrentPoint().quality;  // quality of the current measurement

    		// perform data processing here...
    		// float val = distance;
    		if (startBit) {
      			nsbit++;
    		}
    		if (nsbit > 2) {
      			KickSort<scannedPoint>::quickSort(points, pointInd, KickSort_Dir::ASCENDING);
      			for (int i = 0; i < pointInd; i++) {
        			scannedPoint pointObj = points[i];
        			int objectnum = i + 1;

        			// Serial.print("Point ");
        			// Serial.print(objectnum);
        			// Serial.print(": ");
        			// Serial.print(pointObj.distance);
        			// Serial.print(", ");
        			// Serial.println(pointObj.angle);
      			}
      			// Serial.print("Points captured per scan: ");
      			// Serial.println(datapoints);

      			// Serial.println("------------- NEW SCAN -----------");
      			nsbit = 0;
      			pointInd = 0;
      			datapoints = 0;
      			scannedPoint points[363] = {};
    		} else {
      		// A LiDAR scan contains a lot of bad points with distance = 0, ignore
      		// these. We want a 180 deg fov in front of a user, and take every other
      		// point.
      			if (distance > 0 && (angle >= 270 || angle <= 90)) {
        			if (resolution) {
					      distance=filt.nextEstimate(distance);
					      distaway=cos(depressAngle)*distance;
          			scannedPoint detectedObject = {distance, angle};
          			points[pointInd++] = detectedObject;
          			resolution = not resolution;
					
          				
        			} 
				else {
          				resolution = not resolution; 
        			}
      			}
      			datapoints++;
    		}
	} 
  	else {
    		analogWrite(RPLIDAR_MOTOR, 0);  // stop the rplidar motor

    		// try to detect RPLIDAR...
    		rplidar_response_device_info_t info;
		    //Serial.println("kjhgf");
    		if (IS_OK(lidar.getDeviceInfo(info, 100))) {
      			// detected...
			    //Serial.println("detected");
      			lidar.startScan();

      			// start motor rotating at max allowed speed
      			analogWrite(RPLIDAR_MOTOR, 255);
      			delay(1000);
    		}
  	}
}
