// This file contains the code that enables the text-to-speech functionality of
// NextStep. This file makes use of the Talkie library to implement this
// functionality

#include "vocab.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_US_TI99.h"
#include "Vocab_US_Clock.h"

// Declare a global instance of a Talkie voice
Talkie voice;

// This function instructs the user to enter their height and width measurements
void GetUserInputMessage() {
    voice.say(sp3_WIND);
    voice.say(sp3_NORTHEAST);
    voice.say(sp3_GUSTING_TO);
    voice.say(sp3_FOURTY);
    voice.say(sp3_MILES);
    voice.say(sp3_PER);
    voice.say(sp3_HOUR);
    //voice.say(GETUSERINPUTMESSAGE);
}

// This function instructs the user to turn around 180 degrees. This function
// will be called when the user runs into a large obstacle such as a wall.
void TurnAroundMessage() {
    voice.say(TURNAROUNDMESSAGE);
}

// This function will inform the user of any sensor failures that may make
// further use of NextStep dangerous.
void SensorFailureMessage() {
    voice.say(SENSORFAILUREMESSAGE);
}
