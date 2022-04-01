#include "Sensor.h"


float Sensor::getRange(){
	return range;
}

void Sensor::updatePrevDist(float dist){
	filt.setPrevDist(dist);
}

float Sensor::sensorLoop(){}

Sensor::~Sensor(){}
