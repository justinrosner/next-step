#include "speaker.ino"

//5.5.05
// See if you can press the button once
test(ButtonTest) {
  Serial.println("Starting ButtonTest");
  bool flag = false;
  int counter = 0;
  int buttonState = LOW;
  
  Serial.println("Press the button once");
  while (flag == false && counter < 1000) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH){
      flag = true;
    }
    counter++;
  }
  assertTrue(flag);
}


//5.5.06
// Test if the speaker outputs anything
test(SpeakerTest) {
  bool flag = false;
  int counter = 0;
  int buttonState = LOW;
  Serial.println("Starting SpeakerTest");

  Serial.println("Please listen carefully to the speaker, press the button when you are ready");

  if (readyNextTest) {
    DidYouSayMessage();
  }

  Serial.println("Press the button if you heard the speaker.");
  while (flag == false && counter < 1000) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH){
      flag = true;
    }
    counter++;
  }

  assertTrue(flag);
}
