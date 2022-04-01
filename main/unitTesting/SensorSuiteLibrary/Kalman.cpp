#include "Kalman.h"

Kalman::Kalman()
{
	Q=0;
	R=0;
}

Kalman::Kalman(float mesErr, float modelErr){
	Q=mesErr;
	R=modelErr;
}


Kalman::~Kalman(){
	//end();
	return;
}

void Kalman::setVar(float mesErr, float modelErr){
	Q=mesErr;
	R=modelErr;
}

void Kalman::setDist(float D){
	KalmanData=D; 
}

float Kalman::getDist(){
	return KalmanData;
}

float Kalman::nextEstimate(float dist){
	xtUpdate= xtPrev;
  	ptUpdate= ptPrev + Q;
  
 	Kt=(ptUpdate)/(ptUpdate + R);
  	xt= xtUpdate + (Kt*(dist - xtUpdate));
  	pt=(1-Kt)*ptUpdate;
  	//Serial.println("variance is = " +String(pt));
  	KalmanData=xt;
	xtPrev=xt;
  	ptPrev=pt;
	return KalmanData;
	
}

void Kalman::setPrevDist(float dist){
	xtPrev=dist;
}