// Discover I2C devices. This file lives in the main project tree, so if you
// don't want the discovery function included, define DONE_I2C_DISCOVERY in
// your main.
// See http://playground.arduino.cc/Main/I2cScanner
#ifndef DONE_I2C_DISCOVERY
#define DONE_I2C_DISCOVERY

#include <Arduino.h>
#include <Wire.h>

void PrintHexAddress(byte address) {
  if (address < 16)
    Serial.print("0");
  Serial.print(address, HEX);
}

void PrintI2C() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Scanning for I2C...");
  for (address = 1; address < 127; ++address) {
    // The i2c_scanner uses the return value of the Write.endTransmisstion to
    // see if a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      PrintHexAddress(address);
      Serial.println("");
      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      PrintHexAddress(address);
      Serial.println("");
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}

#endif  // DONE_I2C_DISCOVERY

