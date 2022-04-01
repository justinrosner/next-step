#include "Sensor.h"
#include "RPLidar.h"
#include "system_diagnostic.h"
#include <KickSort.h>

#define RPLIDAR_MOTOR 3

class Lidar: public Sensor{
	public:
		Lidar();
		Lidar(float meaErr, float estErr, float r, float d, float variance, int tx, int rx, SystemDiagnostic dm);
		~Lidar();
		float sensorLoop();
		float getCenter();
	
		RPLidar lidar;
		int nsbit = 0;

		// we want 180 deg of a scan and only take every other point.
		bool resolution = true;

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

		scannedPoint points[363] = {};
		
		int pointInd = 0;
		int datapoints = 0;
		float distaway;
  		float direction;
  		//Q=10;
  		//R=0.0001; // works for ultra sonic sensors
  		//R=0.90;
  		//ptPrev=R;
  		
  private:
    SystemDiagnostic diagnosticModule;
};
