
// Threshold (sound)
int mic_threshold = 500;
// Input pin .. on analog side
int pin_mic = 0;
// Ticks needed to change the state of the system
int ticks_needed = 100;

int mic_value;
int is_on = false;
int ticks = ticks_needed;

void mic()
{
  // Audio value
  mic_value = analogRead(pin_mic);
  Serial.println(mic_value, DEC);
  
  // Is the read value ok? + did we had X ticks of silence?
  if (mic_value >= mic_threshold && ticks > ticks_needed)
  {
    // System on or off?
    if (is_on == 0)
    {
      is_on = 1;
      // Do ACTION 1
    }
    else
    {
      is_on = 0;
      // Do ACTION 2
    }
    ticks = 1;
  }
  else
  {
    if (ticks > ticks_needed)
    {
      ticks = ticks_needed + 1;
    }
    else
    {
      ticks++;
    }
  }
  //Serial.println(mic_value);
  delay(10);
}
