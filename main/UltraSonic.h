#include "Sensor.h"
#include "system_diagnostic.h"
#include <math.h>

class UltraSonic: public Sensor {
	public:
		UltraSonic();
		UltraSonic(int tr, int ec, int a, float d, float meaErr, float estErr, float variance, int centerAngle, SystemDiagnostic::SENSOR_ID iD, SystemDiagnostic dm);
		
		~UltraSonic();
		float getCenter();
		float getDistance();
		float sensorLoop();
	private:
		int trig;
		int echo;
		float distanceUS;
		float duration;
		int direction;
		float distaway;
		SystemDiagnostic::SENSOR_ID sensorID;
    SystemDiagnostic diagnosticModule;
};
