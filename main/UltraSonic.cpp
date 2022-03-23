#include "UltraSonic.h"

UltraSonic::UltraSonic(){}

UltraSonic::UltraSonic(int tr, int ec, int a, float d, float meaErr, float estErr, float variance, int centerAngle){
	filt.setVar(meaErr, estErr);
	range=a;
	depressAngle=d;
	var=variance;
	trig=tr;
	echo=ec;
	pinMode(trig, OUTPUT);
  	pinMode(echo, INPUT);
	direction=centerAngle;
}



float UltraSonic::getCenter(){
	return direction;
}
float UltraSonic::sensorLoop() {
	digitalWrite(trig, LOW);
  	delayMicroseconds(2);

	// Sets the trigPin on HIGH state for 10 micro seconds
  	digitalWrite(trig, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(trig, LOW);

	// Reads the echoPin, returns the sound wave travel time in microseconds
  	duration = pulseIn(echo, HIGH);
  	//Serial.println(digitalRead(echo));
  	//float estimated_x = kf.updateEstimate(duration);
	// Calculating the distance
  	distanceUS= duration*0.0343/2;
  			
  	distaway=filt.nextEstimate(distanceUS);
	//use angle of depress with height to make proer distance calc
	//code
  	distaway=cos(depressAngle)*distanceUS;
  	//Serial.println("distance = " + String(filt.getDist()) + " ");
  	//*Serial.println("ultra sonic dist: "+ String(distanceUS) );
	return distaway;
}

float UltraSonic::getDistance(){
	return distaway;
}

UltraSonic::~UltraSonic(){
	//end();
	return;
}
