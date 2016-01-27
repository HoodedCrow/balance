
#include <Arduino.h>
#include <Wire.h>
#include "MPU6050.h"

int counter = 0;

/*
 * INT -> Digital 2 (interrupt 0)
 * SDA -> Analog 4 (SDA)
 * SCL -> Analog 5 (SCL)
 *
 * VCC -> 3.3 V for now
 * GND
 *
 * Device responds at 0x68.
 */

// No header for this one.
// void PrintI2C();

void setup(void)
{
    pinMode(13, OUTPUT);
    Wire.begin();
    Serial.begin(9600);
    while (!Serial);
    Mpu.WakeUp();
    Mpu.ConfigureGyroOffsets();
}

void loop(void)
{
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(2500);
    Serial.print("At step ");
    Serial.println(++counter);
    Mpu.LoadValues();
    Mpu.PrettyPrint();
    // PrintI2C();
}
