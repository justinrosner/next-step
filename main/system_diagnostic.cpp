// This file contains the code for the class of system diagnostic module.

// Include header files.
#include "Arduino.h"
#include "system_diagnostic.h"

// Initialize class constants
const String SystemDiagnostic::NO_ERROR = "No Error";
const String SystemDiagnostic::ERROR_LIDAR_NO_CONNECTION = "Cannot connect to LiDAR";
const String SystemDiagnostic::ERROR_LIDAR_WRONG_DATA = "LiDAR returning false data";
const String SystemDiagnostic::ERROR_LIDAR_BLOCKED = "LiDAR blocked";
const String SystemDiagnostic::ERROR_LIDAR_BLOCKED_OR_NO_CONNECTION = "LiDAR blocked or disconnected";
const String SystemDiagnostic::ERROR_ULTRASONIC_NO_CONNECTION = "Cannot connect to ultrasonic sensor";
const String SystemDiagnostic::ERROR_ULTRASONIC_WRONG_DATA = "Ultrasonic sensor returning false data";
const String SystemDiagnostic::ERROR_ULTRASONIC_BLOCKED = "Ultrasonic sensor blocked";
const String SystemDiagnostic::ERROR_BUTTON_NO_CONNECTION = "Cannot connect to button";
const String SystemDiagnostic::ERROR_UNKNOWN = "An unknown error occured";
const float SystemDiagnostic::ULTRASONIC_SENSOR_RANGE[4] = {0, 3, 5, 1000};

// Constructor method.
SystemDiagnostic::SystemDiagnostic() {
  for (int i = 0; i < SENSOR_MAX; i++) {
    currentUltrasonicError[i] = NO_ERROR;
    ultrasonicErrorCounter[i] = 0;
    ultrasonicPreviousReading[i] = -1;
  }
  lidarUnblocked = false;
  timeLidarUnblocked = 0;
  buttonState = 0;
}

// Manually set error.
void SystemDiagnostic::error(String errorCode) {
  error(errorCode, SENSOR_NULL, true);
}
void SystemDiagnostic::error(String errorCode, bool confirm) {
  error(errorCode, SENSOR_NULL, confirm);
}
void SystemDiagnostic::error(String errorCode, SENSOR_ID id) {
  error(errorCode, id, true);
}
void SystemDiagnostic::error(String errorCode, SENSOR_ID id, bool confirm) {
  if (id <= SENSOR_MIN || id >= SENSOR_MAX) {
    if (confirm) {
      processError(ERROR_UNKNOWN, SENSOR_NULL, ERROR_COUNTER_THRESHOLD);
    }
    else {
      processError(ERROR_UNKNOWN, SENSOR_NULL, 1);
    }
  }
  else {
    if (confirm) {
      processError(errorCode, id, ERROR_COUNTER_THRESHOLD);
    }
    else {
      processError(errorCode, id, 1);
    }
  }
}

// Check sensor data to determine whether there could be an error.
bool SystemDiagnostic::checkSensor(float reading, SENSOR_ID id) {
  if (id == SENSOR_NULL || id >= SENSOR_MAX || id <= SENSOR_MIN) {
    return false;
  }
  else if (reading >= ULTRASONIC_SENSOR_RANGE[0] || reading <= ULTRASONIC_SENSOR_RANGE[1]) {
    processError(ERROR_ULTRASONIC_NO_CONNECTION, id);
    ultrasonicPreviousReading[id] = reading;
    return true;
  }
  else if (reading < ULTRASONIC_SENSOR_RANGE[2] || reading > ULTRASONIC_SENSOR_RANGE[3]) {
    processError(ERROR_ULTRASONIC_BLOCKED, id);
    ultrasonicPreviousReading[id] = reading;
    return true;
  }
  else if (reading == ultrasonicPreviousReading[id]) {
    processError(ERROR_ULTRASONIC_NO_CONNECTION, id);
    ultrasonicPreviousReading[id] = reading;
    return true;
  }
  else {
    processError(NO_ERROR, id);
    return false;
  }
}

// Process the error to check whether its a false positive or actual error.
void SystemDiagnostic::processError(String errorCode) {
  processError(errorCode, SENSOR_NULL, 1);
}
void SystemDiagnostic::processError(String errorCode, SENSOR_ID id) {
  processError(errorCode, id, 1);
}
void SystemDiagnostic::processError(String errorCode, SENSOR_ID id, byte increment) {
  if (errorCode == NO_ERROR) {
    //Reset the false positive counter on the ultrasonic sensor.
    if (id != SENSOR_NULL) {
      currentUltrasonicError[id] = NO_ERROR;
      ultrasonicErrorCounter[id] = 0;
    }
    else {
      return;
    }
  }
  // Determine whether the ultrasonic sensor error is a false positive or actual error.
  else if (errorCode == ERROR_ULTRASONIC_NO_CONNECTION || errorCode == ERROR_ULTRASONIC_WRONG_DATA || errorCode == ERROR_ULTRASONIC_BLOCKED) {
    if (id != SENSOR_NULL) {
      if (currentUltrasonicError[id] != errorCode) {
        currentUltrasonicError[id] = errorCode;
        ultrasonicErrorCounter[id] = increment;
      }
      else {
        ultrasonicErrorCounter[id] += increment;
      }
      if (ultrasonicErrorCounter[id] >= ERROR_COUNTER_THRESHOLD) {
        outputErrorMessage(errorCode);
      }
    }
    else {
      return;
    }
  }
  // Determine whether the LiDAR error is blocked or no connection.
  else if (errorCode == ERROR_LIDAR_BLOCKED_OR_NO_CONNECTION) {
    // Check if its recently unblocked, if so, the issue is due to no connection.
    if (lidarUnblocked == true && millis()-timeLidarUnblocked >= LIDAR_UNBLOCK_INTERVAL) {
      errorCode = ERROR_LIDAR_NO_CONNECTION;
    }
    // If it is not recently unblocked, first ask the user to try to unblock the LiDAR.
    else {
      errorCode = ERROR_LIDAR_BLOCKED;
    }
  }
  // Output the error message for LiDAR blocked and update the corresponding variables.
  if (errorCode == ERROR_LIDAR_BLOCKED) {
    outputErrorMessage(errorCode);
  }
  // Output the error message for LiDAR no connection error and update the corresponding variables.
  else if (errorCode == ERROR_LIDAR_NO_CONNECTION) {
    outputErrorMessage(errorCode);
    lidarUnblocked = false;
  }
  // Output the error message for LiDAR wrong data error.
  else if (errorCode == ERROR_LIDAR_WRONG_DATA) {
    outputErrorMessage(errorCode);
  }
  // Output the error message for button connection issue.
  else if (errorCode == ERROR_BUTTON_NO_CONNECTION || errorCode == ERROR_UNKNOWN) {
    outputErrorMessage(errorCode);
  }
  // Output the error message for unknown error.
  else if (errorCode == ERROR_UNKNOWN) {
    outputErrorMessage(errorCode);
  }
}

// Output the error message.
void SystemDiagnostic::outputErrorMessage(String errorCode) {
  Serial.println(errorCode);
  if (errorCode == ERROR_LIDAR_BLOCKED) {
    Serial.println("Speaker: Unblock the LiDAR and press the button once.");
    detectButtonPress();
    lidarUnblocked = true;
    timeLidarUnblocked = millis();
  }
}

// Detect the pressing of button
void SystemDiagnostic::detectButtonPress() {
  while(true) {
    // Read the button input
    buttonState = digitalRead(BUTTON_PIN);
    // Check if the button is pressed
    if (buttonState == HIGH) {
      Serial.println("Resetted");
      return;
    }
  }
}
