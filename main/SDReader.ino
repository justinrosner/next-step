// This file contains all of the code pertaining to reading from the SD Card

#include <SPI.h>
#include <SD.h>
#include "TMRpcm.h"

// Wiring connections that need to be used
// DI -> Pin 50
// DO -> Pin 51a
// CLK -> Pin 52
const int chipSelect = 53;
const int cardDetect = 9;

// Global declarations used only in this file
TMRpcm audio;

// This function performs the main setup needed to make suer that the SD card
// is connected
void SDCardSetup() {
  // Check if there is a card connected
  if (!digitalRead(cardDetect)) {
    Serial.println("No card detected. Waiting for card.");
    //delay(250); // 'Debounce insertion'
  } else {
    Serial.println("Card Detected!");
  }

  // Card seems to exist.  begin() returns failure
  // even if it worked if it's not the first call.
  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed!");
  } else {
    Serial.println("Initialization Complete!");
  }

  audio.speakerPin = 6; // Set speaker output to pin 8
  audio.setVolume(5); // Value from 0 - 7
  audio.quality(1); // Set 1 for 2x oversampling, set 0 for normal
}

// This function takes the inputted file name as input and plays the
// corresponding .wav file
void playWAVFile(String fileName) {
  fileName = "/" + fileName;
  Serial.println(fileName);
  File soundFile = SD.open(fileName);
  audio.play(soundFile.name());
}

// This function checks to see if there is an existing file that stores the user
// height information
bool CheckIfFileExists(String fileName) {
  fileName = "/" + fileName;
  Serial.println(fileName);
  if (SD.exists(fileName)) {
    return true;
  } else {
    return false;
  }
}

// This function writes the user height to a file on the SD card
void WriteHeightToSD(int height) {
  // Create the file
  File HeightFile = SD.open("UserHeight.txt", FILE_WRITE);

  // If the file opened okay, write to it
  if (HeightFile) {
    HeightFile.println(String(height));
    HeightFile.close();
  } else {
    // There was an error opening the file
    Serial.println("Error opening UserHeight.txt");
  }
}

// This function reads the user height from a file on the SD card
int ReadHeightFromSD() {
  File HeightFile = SD.open("UserHeight.txt", FILE_WRITE);
  int userHeight = 0;

  // If the file opened okay, read from it
  if (HeightFile) {
    // Read from the file until there is nothing else in it. This should only be
    // one value
    while (HeightFile.available()) {
      userHeight = HeightFile.read();
    }

    // Close the file
    HeightFile.close();
  } else {
    Serial.println("Error opening UserHeight.txt");
  }
  
  return userHeight;
}