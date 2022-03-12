#include "Lidar.h"
#include "UltraSonic.h"

int const len=5;
float dist [len+1];
float alpha=0.01;

int intersect=0;
float distanceFused;
Lidar L; //360
UltraSonic s [len];
void fusionSetup() {
  // put your setup code here, to run once:
  
  s[0]=UltraSonic(28, 29, 15, 12.6, 10, 0.0001, 0.999, 72);//right
  s[1]=UltraSonic(26, 27, 15, 12.6, 10, 0.0001, 0.999, 36); //centerright
  s[2]=UltraSonic(24, 25, 15, 12.6, 10, 0.0001, 0.999, 0); //center
  s[3]=UltraSonic(22, 23, 15, 12.6, 10, 0.0001, 0.999, 324); //centerleft
  s[4]=UltraSonic(30, 31, 15, 12.6, 10, 0.0001, 0.999, 288); //left
  L=Lidar(10, 0.0001, 360, 13.9, 0.0001 , 19, 18);
  

}

void MainSensorFusion() {
  // put your main code here, to run repeatedly:
  int angle;
  for(int i=0; i<len-1; i++){
    dist[i]=s[i].sensorLoop();  
    //check if range intersects with lidar angle measured
    //take out the list of points it is not needed only need current one!
    angle=L.points[L.pointInd].angle;
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
    dist[len-1]=L.distaway/10;  
    //check which bubble the lidar is in and which sensor within this rnge and update it as well as the global array
    if(90>=angle && angle<54){
      if(dist[len-1]<dist[0]){
        fused_distances[0]=dist[len-1];
      }
      else{fused_distances[0]=dist[0];}
    }
    else if(54>=angle && angle<18){
      if(dist[len-1]<dist[1]){
        fused_distances[1]=dist[len-1];
      }
      else{fused_distances[1]=dist[1];}
    }
    else if(angle>=342 || angle<=18){
      if(dist[len-1]<dist[2]){
        fused_distances[2]=dist[len-1];
      }
      else{fused_distances[2]=dist[2];}
    }
    else if(angle<342 && angle>=308){
      if(dist[len-1]<dist[3]){
        fused_distances[3]=dist[len-1];
      }
      else{fused_distances[3]=dist[3];}
    }
    else{
        if(dist[len-1]<dist[4]){
        fused_distances[4]=dist[len-1];
      }
      else{fused_distances[4]=dist[4];}
    }
  }
  else{
    L.updatePrevDist(dist[len]*10);
  }
  
  //return dist;
}

float fuseDist(float distLidar, float distUS){
  distanceFused=distUS*alpha + (1-alpha)*(distLidar/10); 
  return distanceFused;
  
}
