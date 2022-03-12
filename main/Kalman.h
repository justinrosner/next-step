//#include <Adruino.h>
#pragma once
class Kalman{
public:
	Kalman();
	Kalman(float mesErr, float modelErr);
	~Kalman();
	void setVar(float mesErr, float modelErr);
	void setDist(float D);
	float getDist();
	float nextEstimate(float dist);
	void setPrevDist(float dist);
private:
	float KalmanData;
	float xt=10, xtUpdate, xtPrev=10;
	float pt, ptUpdate, ptPrev;
	float Kt, R, Q;

};
