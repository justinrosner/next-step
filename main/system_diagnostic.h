// This is the header file for the system diagnostic module.

// Include header files
#include "Arduino.h"

#ifndef System_Diagnostic_H
#define System_Diagnostic_H

class SystemDiagnostic {
  public:
    SystemDiagnostic();
    static const int BUTTON_PIN = 8;
    static const String NO_ERROR;
    static const String ERROR_UNKNOWN;
    static const String ERROR_BUTTON_NO_CONNECTION;
    static const String ERROR_LIDAR_NO_CONNECTION;
    static const String ERROR_LIDAR_WRONG_DATA;
    static const String ERROR_LIDAR_BLOCKED;
    static const String ERROR_LIDAR_BLOCKED_OR_NO_CONNECTION;
    static const String ERROR_ULTRASONIC_NO_CONNECTION;
    static const String ERROR_ULTRASONIC_WRONG_DATA;
    static const String ERROR_ULTRASONIC_BLOCKED;
    static const String ERROR_ACCELEROMETER_NO_CONNECTION;
    static const String ERROR_ACCELEROMETER_WRONG_DATA;
    enum SENSOR_ID { // Place non-ultrasonic sensor id between null and min.
      SENSOR_MIN = -3,
      SENSOR_ACCELEROMETER = -2,
      SENSOR_NULL = -1,
      SENSOR_RIGHT,
      SENSOR_CENTER_RIGHT,
      SENSOR_CENTER,
      SENSOR_CENTER_LEFT,
      SENSOR_LEFT,
      SENSOR_MAX
    };
    void error(String);
    void error(String, bool);
    void error(String, SENSOR_ID);
    void error(String, SENSOR_ID, bool);
    bool checkSensor(float, SENSOR_ID);
    bool checkAccelerometer(double, double);
  private:
    static const float ULTRASONIC_SENSOR_RANGE[4];
    static const double ACCELEROMETER_RANGE[4];
    static const byte ERROR_COUNTER_THRESHOLD = 5;
    static const unsigned long LIDAR_UNBLOCK_INTERVAL = 300000; // 5 minutes
    String currentUltrasonicError[SENSOR_MAX];
    byte ultrasonicErrorCounter[SENSOR_MAX];
    float ultrasonicPreviousReading[SENSOR_MAX];
    unsigned long timeLidarUnblocked;
    bool lidarUnblocked;
    String currentAccelerometerError;
    byte accelerometerErrorCounter;
    int buttonState;
    void processError(String);
    void processError(String, SENSOR_ID);
    void processError(String, SENSOR_ID, byte);
    void outputErrorMessage(String);
    void detectButtonPress();
};

#endif
