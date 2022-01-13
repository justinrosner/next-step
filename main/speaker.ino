// This file contains the code that enables the text-to-speech functionality of
// NextStep. This file makes use of the Talkie library to implement this
// functionality

// Header files needed for Talkie software to work
#include <arduino.h>
#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_US_TI99.h"
#include "Vocab_US_Clock.h"
#include "Vocab_US_Acorn.h"

// Declare a global instance of a Talkie voice
Talkie voice;

// This function triggers NextStep to relay the start up message to the user
void StartUpMessage() {
    voice.say(spt_HELLO);
    voice.say(spt_IN);
    voice.say(spt_ORDER);
    voice.say(spt_TO);
    voice.say(spt_START);
    voice.say(spt_PLEASE);
    voice.say(spt_SAY);
    voice.say(spt_HOW);
    voice.say(sp3_HIGH);
    voice.say(spt_YOU);
    voice.say(spt_ARE);
}

// This function triggers the "Did you say ..." phase to be asked
void DidYouSayMessage() {
    voice.say(spt_DID);
    voice.say(spt_YOU);
    voice.say(spt_SAY);
}

// This function uses the speaker to relay the desired number
void NumberMessage(int num) {
    // Use a switch statement instead of if-else logic here as it is more
    // efficient for selecting from a large number of values
    switch (num) {
    case 0:
        voice.say(spt_ZERO);
        break;
    case 1:
        voice.say(spt_ONE);
        break;
    case 2:
    voice.say(spt_TWO);
        break;
    case 3:
        voice.say(spt_THREE);
        break;
    case 4:
        voice.say(spt_FOUR);
        break;
    case 5:
        voice.say(spt_FIVE);
        break;
    case 6:
        voice.say(spt_SIX);
        break;
    case 7:
        voice.say(spt_SEVEN);
        break;
    case 8:
        voice.say(spt_EIGHT);
        break;
    case 9:
        voice.say(spt_NINE);
        break;
    default:
        break;
    }
}

// This function relays that the users input was incorrect
void IncorrectMessage() {
    voice.say(spa_INPUT);
    voice.say(spt_NOT);
    voice.say(spt_CORRECT);
    voice.say(spt_PLEASE);
    voice.say(spt_TRY_AGAIN);
}

// This function lets the user know that the device is ready to use
void ReadyMessage() {
    voice.say(spt_DEVICE);
    voice.say(sp4_READY);
}

// This function lets the user know that the battery level is getting low
void LowPowerMessage() {
    voice.say(sp4_WARNING);
    voice.say(sp3_LOW);
    voice.say(sp4_POWER);
}

// This function lets the user know that one of the sensors is broken
void DeviceBrokenMessage() {
    voice.say(sp4_WARNING);
    voice.say(spt_PART);
    voice.say(spt_OF);
    voice.say(spt_DEVICE);
    voice.say(sp3_BROKEN);
}
