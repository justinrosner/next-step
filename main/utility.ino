// This file contains any helper functions that are deemed necessary and are to
// be used across files

// This function checks if a triangle is possible for our selected combination
// of sensor data
int check(float d1, float d2, float a) {
  // int temp_test;
  if (d1 > d2 + a || d2 > d1 + a || a > d2 + d1) {
    return 0;
  } else {
    return 1;
  }
}
