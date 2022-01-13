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
// Says "Hello, in order to start, please say how high you are."
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

// This function triggers NextStep to relay the start up message to the user
// Says "Hello, in order to start, please enter how high you are."
void StartUpMessageButton() {
    voice.say(spt_HELLO);
    voice.say(spt_IN);
    voice.say(spt_ORDER);
    voice.say(spt_TO);
    voice.say(spt_START);
    voice.say(spt_PLEASE);
    voice.say(spt_ENTER);
    voice.say(spt_HOW);
    voice.say(sp3_HIGH);
    voice.say(spt_YOU);
    voice.say(spt_ARE);
}

// This function triggers the message for finding button.
// Says "Find the button on the device and press it one time."
void FindingButtonMessageButton() {
    voice.say(spt_FIRST);
    voice.say(spt_FIND);
    voice.say(spt_THE);
    voice.say(sp2_BUTTON);
    voice.say(spt_ON);
    voice.say(spt_THE);
    voice.say(spt_DEVICE);
    voice.say(spt_AND);
    voice.say(spt_PRESS);
    voice.say(spt_IT);
    voice.say(spt_ONE);
    voice.say(spt_TIME);
}

// This function triggers the "Did you say ..." phase to be asked
// Says "Did you say"
void DidYouSayMessage() {
    voice.say(spt_DID);
    voice.say(spt_YOU);
    voice.say(spt_SAY);
}

// This function triggers the "Did you input ... " phase to be asked
// Says "Did you input"
void DidYouInput() {
    voice.say(spt_DID);
    voice.say(spt_YOU);
    voice.say(spa_INPUT);
}

// This function uses the speaker to relay the desired number
// Says a number between 0 to 9.
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

// This function provide user an example on input height with button
// Says "If you are 1 point 85 meter high, you will first press the button one time and wait for number said back to you."
//       then press the button 8 times and wait for number said back to you. Then press the button 5 times and wait for number said back to you."
void ButtonInputExample() {
    voice.say(spt_IF);
    voice.say(spt_YOU);
    voice.say(spt_ARE);
    NumberMessage(1);
    voice.say(spt_POINT);
    NumberMessage(8);
    NumberMessage(5);
    voice.say(sp2_METER);
    voice.say(sp3_HIGH);
    voice.say(spPAUSE1);
    voice.say(spt_YOU);
    voice.say(spt_WILL);
    voice.say(spt_FIRST);
    voice.say(spt_PRESS);
    voice.say(spt_THE);
    voice.say(spt_BUTTON);
    NumberMessage(1);
    voice.say(spt_TIME);
    voice.say(spt_AND);
    voice.say(spt_WAIT);
    voice.say(spt_FOR);
    voice.say(spt_NUMBER);
    voice.say(spt_SAID);
    voice.say(spt_BACK);
    voice.say(spt_TO);
    voice.say(spt_YOU);
    voice.say(spPAUSE2);
    voice.say(spt_THEN);
    voice.say(spt_PRESS);
    voice.say(spt_THE);
    voice.say(spt_BUTTON);
    NumberMessage(8);
    voice.say(spt_TIME);
    voice.say(spt_AND);
    voice.say(spt_WAIT);
    voice.say(spt_FOR);
    voice.say(spt_NUMBER);
    voice.say(spt_SAID);
    voice.say(spt_BACK);
    voice.say(spt_TO);
    voice.say(spt_YOU);
    voice.say(spPAUSE2);
    voice.say(spt_THEN);
    voice.say(spt_PRESS);
    voice.say(spt_THE);
    voice.say(spt_BUTTON);
    NumberMessage(5);
    voice.say(spt_TIME);
    voice.say(spt_AND);
    voice.say(spt_WAIT);
    voice.say(spt_FOR);
    voice.say(spt_NUMBER);
    voice.say(spt_SAID);
    voice.say(spt_BACK);
    voice.say(spt_TO);
    voice.say(spt_YOU);
}

// This function ask user to input the first digit
// Says "Enter the first number".
void InputFirstDigit() {
    voice.say(spt_ENTER);
    voice.say(spt_THE);
    voice.say(spt_FIRST);
    voice.say(spt_NUMBER);
}

// This function ask user to input the second digit
// Says "Enter the second number".
void InputFirstDigit() {
    voice.say(spt_ENTER);
    voice.say(spt_THE);
    voice.say(spt_SECOND);
    voice.say(spt_NUMBER);
}

// This function ask user to input the third digit
// Says "Enter the third number".
void InputFirstDigit() {
    voice.say(spt_ENTER);
    voice.say(spt_THE);
    voice.say(spt_THIRD);
    voice.say(spt_NUMBER);
}

// This function relays that the users input was incorrect
// Says "Input not correct, please try again."
void IncorrectMessage() {
    voice.say(spa_INPUT);
    voice.say(spt_NOT);
    voice.say(spt_CORRECT);
    voice.say(spt_PLEASE);
    voice.say(spt_TRY_AGAIN);
}

// This function ask user to confirm the input
// Says "Press 2 time for yes, one time for no."
void ButtonConfirmInput() {
    voice.say(spt_PRESS);
    NumberMessage(2);
    voice.say(spt_TIME);
    voice.say(spt_FOR);
    voice.say(spt_YES);
    NumberMessage(1);
    voice.say(spt_TIME);
    voice.say(spt_FOR);
    voice.say(spt_NO);
}

// This function lets the user know that the device is ready to use
// Says "Device ready".
void ReadyMessage() {
    voice.say(spa_THANK);
    voice.say(spt_YOU);
    voice.say(spPAUSE1);
    voice.say(spt_DEVICE);
    voice.say(sp4_READY);
}

// This function lets the user know that the battery level is getting low
// Says "Warning, low power."
void LowPowerMessage() {
    voice.say(sp4_WARNING);
    voice.say(sp3_LOW);
    voice.say(sp4_POWER);
}

// This function lets the user know that one of the sensors is broken
// Says "Warning, part of device broken".
void DeviceBrokenMessage() {
    voice.say(sp4_WARNING);
    voice.say(spt_PART);
    voice.say(spt_OF);
    voice.say(spt_DEVICE);
    voice.say(sp3_BROKEN);
}
