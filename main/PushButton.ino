// This file contains all of the code needed for the button press functionality
// to work properly.

// Import and Define Constants
#include "system_diagnostic.h"
#define YES 2
#define NO 1

typedef void (*Function) ();
Function fun [3]={InputFirstDigit, InputSecondDigit, InputThirdDigit};
// Global variables to be used in this file
byte count=0;
int number [3]={0,0,0};
int height;
String place [3]={"hund", "ten", "ones"};
// variables will change:
int buttonState = 0; // variable for reading the pushbutton status
int previousState=0;
int i;

void ButtonSetup() {
  pinMode(SystemDiagnostic::BUTTON_PIN, INPUT);
}

void GetUserHeight() {
  //Instructions
  StartUpMessageButton();
  delay(1000);
  FindingButtonMessageButton();
  delay(1000);
  ButtonInputExample();
  while (true) {
    //Read the state of the pushbutton value
    height=0;
    for(i=0;i<3;i++){
      while(true){
        buttonStateInpt();
        /*Serial.println(count);
        Serial.print("is " );
        Serial.print(count);
        Serial.print(" your  ");
        Serial.print(place[i] );
        Serial.println(" value?");
        */
        DidYouInput();
        Serial.println("top");
        NumberMessage((int)count);
        Serial.println("bottom");
        number[i]=count;
        //Serial.print("number is::");
        //Serial.println(number[i]);
        //count=0;
        buttonStateInptYN();
        if(count==YES){
          //height=height+((int)number)*pow(10, (2-i));
          Serial.println("yes");
          break;
        }
        count=0;
      }
      count=0;
    }
    //Serial.print("is your Height ");
    //Serial.print(number[0]);
    //Serial.print(number[1]);
    //Serial.println(number[2]);
    DidYouInput();
    NumberMessage((int)number[0]);
    NumberMessage((int)number[1]);
    NumberMessage((int)number[2]);
    buttonStateInptYN();
    if (count==YES){
      ReadyMessage();
      return;
    }
  }
}

byte buttonStateInpt(){
  byte idleCount=0;
  count=0;
  Serial.println("inputtop");
  fun[i]();
  Serial.println("inputbottom");
  //Serial.print("enter position for ");
  //Serial.println(place[i]);
  //NumberMessage(i);
  while(idleCount<30){
    buttonState = digitalRead(SystemDiagnostic::BUTTON_PIN);
    //Serial.println(count);
    if(count==9 ){
      return count;  
    }
    /**else if(idleCount==30){
      Serial.print("is", count, "your output?")  ;
      delay(1000);
      buttonState = digitalRead(SystemDiagnostic::BUTTON_PIN);
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
  //Serial.println("ending 3 sec idle");
  return count;
}

byte buttonStateInptYN(){
  byte noInputCount = 0;
  while (true) {
    count=0;
    byte idleCount=0;
    //Serial.println("YES OR NO");
    delay(2000);
    ButtonConfirmInput();
    while(idleCount<30){
      buttonState = digitalRead(SystemDiagnostic::BUTTON_PIN);
      //Serial.println(count);
      if(count==9 ){
        return count;  
      }
      /**else if(idleCount==30){
        Serial.print("is", count, "your output?")  ;
        delay(1000);
        buttonState = digitalRead(SystemDiagnostic::BUTTON_PIN);
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
    //Serial.println("ending 3 sec idle");
    if (count != 0) {
      return count;
    }
    else {
      noInputCount++;
      if (noInputCount >= 3) {
        diagnosticModule.error(SystemDiagnostic::ERROR_BUTTON_NO_CONNECTION);
        return 0;
      }
    }
  }
}
