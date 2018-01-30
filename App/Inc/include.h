#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"
#include  "math.h"
/*
 * Include 用户自定义的头文件
 */
//#include  "MK60_wdog.h"
#include  "MK60_gpio.h"     //IO口操作
#include  "MK60_uart.h"     //串口
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"    //低功耗定时器(延时)
#include  "MK60_i2c.h"      //I2C
#include  "MK60_spi.h"      //SPI
#include  "MK60_ftm.h"      //FTM
#include  "MK60_pit.h"      //PIT
#include  "MK60_rtc.h"      //RTC
#include  "MK60_adc.h"      //ADC
#include  "MK60_FLASH.h"    //FLASH
#include  "MK60_it.h"    //中断

#include  "FIRE_LED.H"          //LED
#include  "FIRE_KEY.H"          //KEY
#include  "FIRE_RTC_count.h"    //RTC 时间转换

#include "OLED.h"
#include "All_config.h"
#include "MK60_it.h"
#include "Helper.h"
#include "mpu6050.h" 

//*****************模糊算法*********************************
//E         0    9    18   27   36   45   54   63   72   80
//zero      1   0.2   0    0    0    0    0    0    0    0
//tiny     0.2   1   0.2   0    0    0    0    0    0    0
//tinysmall 0   0.2   1   0.2   0    0    0    0    0    0
//small     0    0   0.3   1   0.3   0    0    0    0    0
//smallmid  0    0    0   0.3   1   0.3   0    0    0    0
//middle    0    0    0    0   0.4   1   0.4   0    0    0 
//midbig    0    0    0    0   0.1   0.5   1   0.5  0.1  0
//big       0    0    0    0    0   0.1   0.5   1   0.5  0.1
//bighuge   0    0    0    0    0    0   0.2   0.6   1   0.6   
//huge      0    0    0    0    0    0    0   0.2   0.6   1

//EC   -4   -2    0    2    4   
//nl    1    0    0    0    0
//ns    0    1    0    0    0
//z     0    0    1    0    0
//ns    0    0    0    1    0
//nl    0    0    0    0    1

//   E         0    1    2    3    4    5    6    7    8    9
//  U
// EC
// -4          z    
// -2          z
//  0          z    t    ts   s    sm   m    mb   b    bh   h
//  2          z    s    sm   m    mb   b    bh   bh   h    h
//  4          z    

//**转角（偏差）**
#define zero      0
#define tiny      5
#define tinysmall 20
#define small     40
#define smallmid  70
#define middle    90
#define midbig    110
#define big       130
#define bighuge   160
#define huge      190

//***********************************************


#define pos_ref  0
#define turn_val 0
#define dutymax 900

//电感名称  
#define     R_xie       ADC1_SE8       // PTB0
#define     R_zhi	ADC1_SE9       // PTB1
#define     R_heng      ADC1_SE10      // PTB4
#define     M_heng	ADC1_SE11      // PTB5
#define     M_zhi	ADC1_SE12      // PTB6
#define     L_heng	ADC1_SE13      // PTB7
#define     L_zhi 	ADC1_SE14      // PTB10
#define     L_xie	ADC1_SE15      // PTB11

//陀螺仪名称   
#define XOUT ADC0_SE16       //ADC0_SE16
#define YOUT ADC0_SE17       //PTE24
#define ZOUT ADC0_SE18       //PTE25

//加速度计相关   
#define MMA7361_BEF              2965
#define MMA7361_AFT              970
#define MMA7361_ratio            180/(MMA7361_BEF-MMA7361_AFT)

extern int strategy;
   
//平衡   
#define MMA7361_vertical      1975//零偏数值
#define GYRO_VAL              290//陀螺仪静止输出,290
#define GRAVITY_ADJUST_TIME_CONSTANT       4  //1//4
#define DT                    0.005//200hz，即5ms
#define Gyro_ratio            0.0046//0.0023//0.0115

//电机pid设置
#if ((strategy==1)|(strategy==2))

#define      P_ANGLE 260//260//240  、、//300
#define      D_ANGLE 10//0//1.5        //2

#elif ((strategy==3)|(strategy==4))

#define      P_ANGLE 260//260//240  、、//300
#define      D_ANGLE 10//0//1.5        //2

#else

#define      P_ANGLE 260//260//240  、、//300
#define      D_ANGLE 10//0//1.5        //2

#endif

#define deadval_L  0//0
#define deadval_R  0//40

#define  OPTICAL_ENCODE_CONSTANT    200 // 光电编码盘的刻槽数量
#define  SPEED_CONTRO_PERIOD        100 // 速度控制周期， ms
#define  CAR_SPEED_CONSTANT         2000.0/(SPEED_CONTROL_PEIORD*OPTICAL_ENCODE_CONSTANT)  //单位转化比例值1000.0/(SPEED_CONTROL_PEIORD*OPTICAL_ENCODE_CONSTANT)

//变量声明
//*************************启停车部分*****************************************
extern uint8 count_ad,Flag_Stop,Flag_Start,Flag_Stop_F,Flag_Slope;
extern uint16 Counter_Start,Counter_Stop,Counter_Slope;
//uint16 Distance0 = 0,Distance1 = 1;
//*************************虚拟示波器*****************************************
extern float var[3];
void PORTE_IRQHandler(void);


//*************************oled部分*****************************************
extern uint8 code[2][6];
//*************************归一化初值********************************************
extern int reference1,reference2;
extern int zhuansuL,zhuansuR;

extern int hundred_t;//mk60_it
//*************************电感值********************************************
extern unsigned char      left_hou  ;
extern unsigned char      left_zhi  ;
extern unsigned char      left_heng ;
extern unsigned char      mid_heng  ;
extern unsigned char      mid_zhi   ;
extern unsigned char      right_heng;
extern unsigned char      right_zhi ;
extern unsigned char      right_hou ;

extern unsigned char  AD[8][5];

//***************************printf显示****************************************
extern long int GYRO_X,GYRO_Z;
extern float g_fCarAngle;
extern float   pos_kp ; 
extern float   pos_kd ;

extern int cha_zhi0,cha_zhi1,cha_zhi2,he_zhi0,he_zhi2,last_turn;
extern int midheng,midzhi;
extern int result;
extern int error1;
extern int pos_error;
extern int stop_flag;
//*********************************************************************************
typedef struct  
{
  float pos_com;
  int   pos_up;
  int   pos_down;
  int   pos_avr;
  
  float ACC_Kp;//15
  float ACC_Ki;//0.01
  float ACC_Kd;//7
  float CAR_SPEED_SETfDelta;
  
  float turn_D;
  
  float Angel_set;//39
}date_speed;

extern date_speed plan;

//************************************************************************************
//*****十字*******
extern char shizi_flag;
//*****直道*******
extern unsigned int zhidao_flag;
extern int pos_up,pos_ud;
#endif  //__INCLUDE_H__
