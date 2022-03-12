/*
  Button
  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.
  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground
  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.
  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe
  This example code is in the public domain.
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

#define YES 2
#define NO 1
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
byte count=0;
int hieght;
String place [3]={"hund", "ten", "ones"};
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int previousState=0;
int i;
void setup() {
  // initialize the LED pin as an output:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  hieght=0;
  // read the state of the pushbutton value:
  for(i=0;i<3;i++){
    while(true){
      buttonStateInpt();
      Serial.println(count);
      Serial.print("is " );
      Serial.print(count);
      Serial.print(" your  ");
      Serial.print(place[i] );
      Serial.println(" value?");
      
      int number=count;
      
      //count=0;
      buttonStateInptYN();
      if(count==YES){
        hieght=hieght+((int)number)*pow(10, (2-i))+1;
        
        break;
      }
      //count=0;
    }
    //count=0;
  }
  Serial.print("is your Height ");
  Serial.println(hieght);
  
}

byte buttonStateInpt(){
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
    /**else if(idleCount==30){
      Serial.print("is", count, "your output?")  ;
      delay(1000);
      buttonState = digitalRead(buttonPin);
    }*/
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
    // turn LED on:
    //digitalWrite(ledPin, HIGH);
      if(previousState!=buttonState){
        count++;  
        idleCount=0;
      }
      
    
    } else {
    // turn LED off:
    //digitalWrite(ledPin, LOW);
      idleCount++;
    }
    delay(100);
    previousState=buttonState;  
  }
  Serial.println("ending 3 sec idle");
  
  return count;
}

byte buttonStateInptYN(){
  count=0;
  byte idleCount=0;
  Serial.println("YES OR NO");
  
  while(idleCount<30){
    buttonState = digitalRead(buttonPin);
    //Serial.println(count);
    if(count==9 ){
    
      return count;  
    }
    /**else if(idleCount==30){
      Serial.print("is", count, "your output?")  ;
      delay(1000);
      buttonState = digitalRead(buttonPin);
    }*/
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
    // turn LED on:
    //digitalWrite(ledPin, HIGH);
      if(previousState!=buttonState){
        count++;  
        idleCount=0;
      }
      
    
    } else {
    // turn LED off:
    //digitalWrite(ledPin, LOW);
      idleCount++;
    }
    delay(100);
    previousState=buttonState;  
  }
  Serial.println("ending 3 sec idle");
  
  return count;
}
