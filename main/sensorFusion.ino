#include "Lidar.h"
#include "UltraSonic.h"

int const len=5;
float dist [len+1];
float alpha=0.01;

int intersect=0;
float distanceFused;
Lidar L(10, 0.0001, 360, 13.9, 0.0001 , 19, 18); //360
UltraSonic s [len];
void fusionSetup() {
  // put your setup code here, to run once:
  
  s[0]=UltraSonic(28, 29, 15, 12.6, 10, 0.0001, 0.999, 72);//right
  s[1]=UltraSonic(26, 27, 15, 12.6, 10, 0.0001, 0.999, 36); //centerright
  s[2]=UltraSonic(24, 25, 15, 12.6, 10, 0.0001, 0.999, 0); //center
  s[3]=UltraSonic(22, 23, 15, 12.6, 10, 0.0001, 0.999, 324); //centerleft
  s[4]=UltraSonic(30, 31, 15, 12.6, 10, 0.0001, 0.999, 288); //left
   
  

}

float [] fusionLoop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<len-1; i++){
    dist[i]=s[i].sensorLoop();  
    //check if range intersects with lidar angle measured
    //take out the list of points it is not needed only need current one!
    int angle=L.points[L.pointInd].angle;
    if(angle<=s[i].getCenter()+s[i].getRange()/2 && angle>=s[i].getCenter()-s[i].getRange()/2){
       dist[i]=fuseDist(L.distaway, s[i].getDistance()) ;
       dist[len]=dist[i];
       //set the previous distance xtprev to this distance!
       s[i].updatePrevDist(dist[i]);
       //add this funtion within the sensors
       intersect=1;
    }
    
    
    delay(10);
  }
  if(!intersect){
    //output distance of lidar as well and angle it was detecting at for bubble band! 
    dist[len-1]=L.sensorLoop();  
  }
  else{
    L.updatePrevDist(dist[len]*10);
  }
  
  return dist;
}

float fuseDist(float distLidar, float distUS){
  distanceFused=distUS*alpha + (1-alpha)*(distLidar/10); 
  return distanceFused;
  
}
