# Interpolation for OBD2 data

I'm currently working on a similar ESP32 + Bluetooth/WiFi OBD2 dongle solution. I discovered that the cheap Chinese BT/WiFi OBD2 dongles can only read data every 200-300ms, with significant variation in the delay. To reduce lag, I measure the time between data readings and use interpolation to smooth the values (e.g. speed) by transitioning between the previous and new values over that time period.

https://www.elmelectronics.com/obdtips.html#UnderstandingOBD
According to this source , early OBD standards required that scan tools not request data more frequently than every 100ms.
"The early standards required that scan tools not request information more often than every 100msec."

Here is video which demonstrates how my interpolation solution reduces that laggy, but surely it is doing some quess work for current speed between readings (200ms), but looks much nicer.
https://www.youtube.com/watch?v=8rYSY2oQVZ8



Here simple solution to interpolate between two values:
```
newValue is new value from OBD2
interpolationDuration is delay between OBD2 two data readings
outValue is interpolated value to display
previousValue to store previous value (interpolation starting value)
currentValue is target value (interpolation ending value)
runTime to store how long interpolation have already been running
```

```
void InterpolateValues(float newValue, unsigned long interpolationDuration, float &outValue, float &previousValue, float &currentValue, unsigned long &runTime)
{
  if (interpolationDuration == 0)
  {
    outValue = newValue;
    return;
  }

  unsigned long currentMillis = millis();

  if (newValue != currentValue)
  {
    // New value should stop current interpolation
    previousValue = outValue;
    currentValue = newValue;
    runTime = currentMillis;
  }
  else if (currentMillis - runTime >= interpolationDuration)
  {
    // Current interpolation comes to end
    previousValue = currentValue;
    currentValue = newValue;
    runTime = currentMillis;
  }

  //  Calculate interpolation t and clamp it between 0 and 1
  float t = (float)(currentMillis - runTime) / interpolationDuration;
  if (t > 1.0f)
    t = 1.0f;
  if (t < 0.0f)
    t = 0.0f;

  //  Interpolated value
  outValue = previousValue + t * (currentValue - previousValue);
}
```
