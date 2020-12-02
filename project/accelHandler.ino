#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

// i2c
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

void setupGestures() {
  FIRMATADEBUG.println("Setting up LSM");
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    FIRMATADEBUG.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);


  delay(1);
}

void handleAccelGestures(){
  
  // Read the accelerometer data here and send messages if swipe or tap is detected
  lsm.read();

  FIRMATADEBUG.print("X: "); Serial.print((int)lsm.gyroData.x);   FIRMATADEBUG.print(" ");
  FIRMATADEBUG.print("Y: "); FIRMATADEBUG.print((int)lsm.gyroData.y);        FIRMATADEBUG.print(" ");
  FIRMATADEBUG.print("Z: "); FIRMATADEBUG.println((int)lsm.gyroData.z);      FIRMATADEBUG.println(" ");

  if (lsm.gyroData.z > 15000) {
    FIRMATADEBUG.println("Left Swipe");
    bluefruit.write("l");
  } else if (lsm.gyroData.z < -15000) {
    FIRMATADEBUG.println("Right Swipe");
    bluefruit.write("r");
  }
  if (lsm.gyroData.y > 8000) {
    FIRMATADEBUG.println("Toe Tap");
    bluefruit.write("t");
  }

  delay(200);

}
  
