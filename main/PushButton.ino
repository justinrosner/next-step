// This file contains all of the code needed for the button press functionality
// to work properly.

// Define Constants
#define YES 2
#define NO 1

// Set pins
const int buttonPin = 13;

// Global variables to be used in this file
byte count=0;
String place [3]={"hund", "ten", "ones"};
int buttonState = 0;         // variable for reading the pushbutton status
int previousState=0;
int i;

void ButtonSetup() {
  pinMode(buttonPin, INPUT);
}

void GetUserHeight() {
  int height=0;
  // read the state of the pushbutton value:
  for(i=0;i<3;i++){
    while(true){
      buttonStateInput();
      Serial.println(count);
      Serial.print("is " );
      Serial.print(count);
      Serial.print(" your  ");
      Serial.print(place[i] );
      Serial.println(" value?");
      
      int number = count;
      
      buttonStateInputYN();
      if(count==YES){
        height=height + ((int)number)*pow(10, (2-i))+1;
        
        break;
      }
    }
  }
  Serial.print("is your Height ");
  Serial.println(height);
}

byte buttonStateInput(){
  byte idleCount=0;
  count=0;
  Serial.print("enter position for ");
  Serial.println(place[i]);
  while(idleCount<30){
    buttonState = digitalRead(buttonPin);
    //Serial.println(count);
    if(count==9 ){
    
      return count;  
    }

    if (buttonState == HIGH) {
      if(previousState!=buttonState){
        count++;  
        idleCount=0;
      }
      
    
    } else {
      idleCount++;
    }
    delay(100);
    previousState=buttonState;  
  }
  Serial.println("ending 3 sec idle");
  
  return count;
}

byte buttonStateInputYN(){
  count=0;
  byte idleCount=0;
  Serial.println("YES OR NO");
  
  while(idleCount<30){
    buttonState = digitalRead(buttonPin);
    if(count==9 ){
      return count;  
    }

    if (buttonState == HIGH) {
      if(previousState != buttonState){
        count++;  
        idleCount=0;
      }   
    } else {
      idleCount++;
    }
    delay(100);
    previousState = buttonState;  
  }
  Serial.println("ending 3 sec idle");
  
  return count;
}
