#include "include.h"


uint8 DATA_H,DATA_L,data;

//*********mpu6050初始化*************************
uint8 mpu6050_init()                                   //mpu6050初始化
{
  i2c_init(I2C0, baud_n);
  DELAY_MS(300);
  i2c_write_reg(I2C0,SlaveAddress,PWR_MGMT_1,0x00);     //解除休眠状态
  i2c_write_reg(I2C0,SlaveAddress,SMPLRT_DIV,0x04);
  i2c_write_reg(I2C0,SlaveAddress,CONFIG,0x00);

  //下面两个寄存器可以设置转换后数据的精度   0x08 最大值为 8192 (2^13)
  i2c_write_reg(I2C0,SlaveAddress,GYRO_CONFIG,0x08);    //
  i2c_write_reg(I2C0,SlaveAddress,ACCEL_CONFIG,0x00);   //

  data = i2c_read_reg(I2C0,SlaveAddress,WHO_AM_I);
 //data = i2c_read_reg(I2C0,SlaveAddress,PWR_MGMT_1);
 // while(1)
   // printf("%d\n",data);
  if(data == 0x68)
    return 1;
  else 
    return 0;
}

//*********读 加速度计X轴 数据*******************
int16 mpu6050_ACCEL_X_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,ACCEL_XOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,ACCEL_XOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********读 加速度计Y轴 数据*******************
int16 mpu6050_ACCEL_Y_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,ACCEL_YOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,ACCEL_YOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********读 加速度计Z轴 数据*******************
int16 mpu6050_ACCEL_Z_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,ACCEL_ZOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,ACCEL_ZOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********读 陀螺仪计X轴 数据*******************
int16 mpu6050_GYRO_X_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,GYRO_XOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,GYRO_XOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********读 陀螺仪计Y轴 数据*******************
int16 mpu6050_GYRO_Y_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,GYRO_YOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,GYRO_YOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********读 陀螺仪计Z轴 数据*******************
int16 mpu6050_GYRO_Z_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,GYRO_ZOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,GYRO_ZOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********读 温度 数据*******************
int16 mpu6050_TEMP_OUT_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,TEMP_OUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,TEMP_OUT_L);
  return (DATA_H<<8)+DATA_L;
}
