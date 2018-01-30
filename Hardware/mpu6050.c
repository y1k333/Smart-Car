#include "include.h"


uint8 DATA_H,DATA_L,data;

//*********mpu6050��ʼ��*************************
uint8 mpu6050_init()                                   //mpu6050��ʼ��
{
  i2c_init(I2C0, baud_n);
  DELAY_MS(300);
  i2c_write_reg(I2C0,SlaveAddress,PWR_MGMT_1,0x00);     //�������״̬
  i2c_write_reg(I2C0,SlaveAddress,SMPLRT_DIV,0x04);
  i2c_write_reg(I2C0,SlaveAddress,CONFIG,0x00);

  //���������Ĵ�����������ת�������ݵľ���   0x08 ���ֵΪ 8192 (2^13)
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

//*********�� ���ٶȼ�X�� ����*******************
int16 mpu6050_ACCEL_X_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,ACCEL_XOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,ACCEL_XOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********�� ���ٶȼ�Y�� ����*******************
int16 mpu6050_ACCEL_Y_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,ACCEL_YOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,ACCEL_YOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********�� ���ٶȼ�Z�� ����*******************
int16 mpu6050_ACCEL_Z_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,ACCEL_ZOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,ACCEL_ZOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********�� �����Ǽ�X�� ����*******************
int16 mpu6050_GYRO_X_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,GYRO_XOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,GYRO_XOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********�� �����Ǽ�Y�� ����*******************
int16 mpu6050_GYRO_Y_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,GYRO_YOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,GYRO_YOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********�� �����Ǽ�Z�� ����*******************
int16 mpu6050_GYRO_Z_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,GYRO_ZOUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,GYRO_ZOUT_L);
  return (DATA_H<<8)+DATA_L;
}
//*********�� �¶� ����*******************
int16 mpu6050_TEMP_OUT_data()                                    
{
  DATA_H = i2c_read_reg(I2C0,SlaveAddress,TEMP_OUT_H);
  DATA_L = i2c_read_reg(I2C0,SlaveAddress,TEMP_OUT_L);
  return (DATA_H<<8)+DATA_L;
}
