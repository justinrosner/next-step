#include "Kalman.h"
#include "Arduino.h"
#pragma once

class Sensor{
public://add height that we get from user input!!!!!!!
	int range; //relative to center
	float depressAngle;
	float var;
	Kalman filt;
	
	float getRange();
	void updatePrevDist(float dist);
	//virtual Sensor(float d, int a, float meaErr, float estErr):filt(Kalman(meaErr, estErr));

	virtual float sensorLoop();

	virtual ~Sensor();



};