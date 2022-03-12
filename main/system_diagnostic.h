// This is the header file for the system diagnostic module.

// Include header files
#include "Arduino.h"

#ifndef System_Diagnostic_H
#define System_Diagnostic_H

class SystemDiagnostic {
  public:
    SystemDiagnostic();
    static const String NO_ERROR;
    static const String ERROR_BUTTON_NO_CONNECTION;
    static const String ERROR_UNKNOWN;
    static const int BUTTON_PIN = 13;
    static const String ERROR_LIDAR_NO_CONNECTION;
    static const String ERROR_LIDAR_WRONG_DATA;
    static const String ERROR_LIDAR_BLOCKED;
    static const String ERROR_LIDAR_BLOCKED_OR_NO_CONNECTION;
    static const String ERROR_ULTRASONIC_NO_CONNECTION;
    static const String ERROR_ULTRASONIC_WRONG_DATA;
    static const String ERROR_ULTRASONIC_BLOCKED;
    enum SENSOR_ID {
      SENSOR_MIN = -2,
      SENSOR_NULL = -1,
      SENSOR_LEFT,
      SENSOR_FRONT_LEFT,
      SENSOR_FRONT,
      SENSOR_FRONT_RIGHT,
      SENSOR_RIGHT,
      SENSOR_MAX
    };
    void error(String);
    void error(String, bool);
    void error(String, SENSOR_ID);
    void error(String, SENSOR_ID, bool);
    bool checkSensor(float, SENSOR_ID);
  private:
    static const float ULTRASONIC_SENSOR_RANGE[4];
    static const byte ERROR_COUNTER_THRESHOLD = 5;
    static const unsigned long LIDAR_UNBLOCK_INTERVAL = 5*60*1000UL;
    String currentUltrasonicError[SENSOR_MAX];
    byte ultrasonicErrorCounter[SENSOR_MAX];
    float ultrasonicPreviousReading[SENSOR_MAX];
    bool lidarUnblocked;
    unsigned long timeLidarUnblocked;
    int buttonState;
    void processError(String);
    void processError(String, SENSOR_ID);
    void processError(String, SENSOR_ID, byte);
    void outputErrorMessage(String);
    void detectButtonPress();
};

#endif
