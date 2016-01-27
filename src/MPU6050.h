/*
 * MPU6050.h
 *
 *  Created on: Jan 24, 2016
 *      Author: tatiana
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include <Arduino.h>

class Mpu6050 {
public:
  static const int kMpuAddress = 0x68;
  void WakeUp();
  void ConfigureGyroOffsets();
  void LoadValues();
  void PrettyPrint();


  // AFS_SEL = 0 (2g), 1 (4g), 2 (8g), 3 (16g) -> per g 16384, 8192, 4096, 2048
  static const double kAccelPerG = 8192.0;
  double AccelX() { return accel_x_ / kAccelPerG; }
  double AccelY() { return accel_y_ / kAccelPerG; }
  double AccelZ() { return accel_z_ / kAccelPerG; }
  double TemperatureC() { return (temperature_ + 12412.0) / 340.0; }
  // FS_SEL = 0 (250 dps), 1 (500 dps), 2 (1000 dps), 3 (2000 dps) ->
  // bits per dps 131, 65.5, 32.8, 16.4
  static const double kGyroDps = 65.5;
  double GyroX() { return (gyro_x_ - gyro_offset_x_) / kGyroDps; }
  double GyroY() { return (gyro_y_ - gyro_offset_y_) / kGyroDps; }
  double GyroZ() { return (gyro_z_ - gyro_offset_z_) / kGyroDps; }
private:
  void WriteRegister(byte addr, byte value);

  int16_t accel_x_, accel_y_, accel_z_;
  int16_t temperature_;
  int16_t gyro_x_, gyro_y_, gyro_z_;
  int16_t gyro_offset_x_, gyro_offset_y_, gyro_offset_z_;
};

extern Mpu6050 Mpu;

#endif /* MPU6050_H_ */
