// See http://playground.arduino.cc/Main/MPU-6050#short
#include "MPU6050.h"
#include <Wire.h>

/*
 * After boot, wake up, no initialization
 * Acceleration:
 * -508 -> -0.12 g
 * -800 -> -0.20 g
 * 16928 -> 4.13 g
 * Temperature: -4112 -> 24.41 C
 * Gyros:
 * -475 -> -7.25 dps
 * 221 -> 3.37 dps
 * 61 -> 0.93 dps
 *
 */

void Mpu6050::WriteRegister(byte addr, byte value) {
  Wire.beginTransmission(kMpuAddress);
  Wire.write(addr);
  Wire.write(value);
  Wire.endTransmission(true);
}


void Mpu6050::WakeUp() {
  // In PWR_MGMT_1 register, clear bit 6 (sleep), set bits 2-0 to 001 to clock
  // from gyro x.
  WriteRegister(0x6B, 0x01);
  // GYRO_CONFIG, bits 4,3 = 01 -> range +-500 dps
  WriteRegister(0x1B, 0x08);
  // ACCEL_CONFIG, bits 4,3 = 01 -> range +-4g
  WriteRegister(0x1C, 0x08);
}

void Mpu6050::ConfigureGyroOffsets() {
  gyro_offset_x_ = 0;
  gyro_offset_y_ = 0;
  gyro_offset_z_ = 0;
  for (int i = 0; i < 30; ++i) {
    LoadValues();
    gyro_offset_x_ += gyro_x_;
    gyro_offset_y_ += gyro_y_;
    gyro_offset_z_ += gyro_z_;
  }
  gyro_offset_x_ /= 30;
  gyro_offset_y_ /= 30;
  gyro_offset_z_ /= 30;
}

void Mpu6050::LoadValues() {
  Wire.beginTransmission(kMpuAddress);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);

  // Request a total of 14 registers
  Wire.requestFrom(kMpuAddress, 14, true);
  // 0x3B is high, 0x3C is low.
  accel_x_ = Wire.read() << 8 | Wire.read();
  accel_y_ = Wire.read() << 8 | Wire.read();
  accel_z_ = Wire.read() << 8 | Wire.read();
  temperature_ = Wire.read() << 8 | Wire.read();
  gyro_x_ = Wire.read() << 8 | Wire.read();
  gyro_y_ = Wire.read() << 8 | Wire.read();
  // 0x47 is high, 0x48 is low.
  gyro_z_ = Wire.read() << 8 | Wire.read();
}

static const char kArrow[] = " -> ";
static const char kGtext[] = " g";
static const char kDps[] = " dps";

void Mpu6050::PrettyPrint() {
  Serial.println("Acceleration: ");
  Serial.print(accel_x_); Serial.print(kArrow);
  Serial.print(AccelX()); Serial.println(kGtext);
  Serial.print(accel_y_); Serial.print(kArrow);
  Serial.print(AccelY()); Serial.println(kGtext);
  Serial.print(accel_z_); Serial.print(kArrow);
  Serial.print(AccelZ()); Serial.println(kGtext);
  Serial.print("Temperature: ");
  Serial.print(temperature_); Serial.print(kArrow);
  Serial.print(TemperatureC()); Serial.println(" C");
  Serial.println("Gyros: ");
  Serial.print(gyro_x_); Serial.print(kArrow);
  Serial.print(GyroX()); Serial.println(kDps);
  Serial.print(gyro_y_); Serial.print(kArrow);
  Serial.print(GyroY()); Serial.println(kDps);
  Serial.print(gyro_z_); Serial.print(kArrow);
  Serial.print(GyroZ()); Serial.println(kDps);
}

Mpu6050 Mpu;
