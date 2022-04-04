// This is the header file for the system diagnostic module.

// Include header files
#include "Arduino.h"

#ifndef System_Diagnostic_H
#define System_Diagnostic_H

class SystemDiagnostic {
  public:
    SystemDiagnostic();
    static const int BUTTON_PIN = 13;
    enum ERROR_CODE {
      NO_ERROR,
      ERROR_UNKNOWN,
      ERROR_BUTTON_NO_CONNECTION,
      ERROR_LIDAR_NO_CONNECTION,
      ERROR_LIDAR_WRONG_DATA,
      ERROR_LIDAR_BLOCKED,
      ERROR_LIDAR_BLOCKED_OR_NO_CONNECTION,
      ERROR_ULTRASONIC_NO_CONNECTION,
      ERROR_ULTRASONIC_WRONG_DATA,
      ERROR_ULTRASONIC_BLOCKED,
      ERROR_ACCELEROMETER_NO_CONNECTION,
      ERROR_ACCELEROMETER_WRONG_DATA
    };
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
    void error(ERROR_CODE);
    void error(ERROR_CODE, bool);
    void error(ERROR_CODE, SENSOR_ID);
    void error(ERROR_CODE, SENSOR_ID, bool);
    bool checkSensor(float, SENSOR_ID);
    bool checkAccelerometer(double, double);
  private:
    static float ULTRASONIC_SENSOR_RANGE[4];
    static double ACCELEROMETER_RANGE[4];
    static const byte ERROR_COUNTER_THRESHOLD = 5;
    static const unsigned long LIDAR_UNBLOCK_INTERVAL = 300000; // 5 minutes
    ERROR_CODE currentUltrasonicError[SENSOR_MAX];
    byte ultrasonicErrorCounter[SENSOR_MAX];
    float ultrasonicPreviousReading[SENSOR_MAX];
    unsigned long timeLidarUnblocked;
    bool lidarUnblocked;
    ERROR_CODE currentAccelerometerError;
    byte accelerometerErrorCounter;
    int buttonState;
    void processError(ERROR_CODE);
    void processError(ERROR_CODE, SENSOR_ID);
    void processError(ERROR_CODE, SENSOR_ID, byte);
    void outputErrorMessage(ERROR_CODE);
    void detectButtonPress();
};

#endif
