/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,野火科技
 *     All rights reserved.
 *     技术讨论：野火初学论坛 http://www.chuxue123.com
 *
 *     除注明出处外，以下所有内容版权均属野火科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留野火科技的版权声明。
 *
 * @file       MK60_it.c
 * @brief      野火K60 平台中断复位函数
 * @author     野火科技
 * @version    v5.0
 * @date       2013-06-26
 */

#include "include.h"
int hundred_t,acc_t,stop_flag=0;
long int GYRO_X,GYRO_Z;  
void PORTE_IRQHandler(void);
void PIT0_IRQHandler(void)
{

    ad_get(); 
    GYRO_X=mpu6050_GYRO_X_data();
    pid_bal();

    GYRO_Z=mpu6050_GYRO_Z_data();
    pid_turn();
//    if(GYRO_Z<0)
//      GYRO_Z=3*GYRO_Z/4;

    pid_acc();
    FTM_mot();
    hundred_t++;
    
  if(hundred_t==10)//20
  {
//   acc_t++;
   zhuansuL =-FTM_QUAD_get(FTM1);          //获取FTM 正交解码 的脉冲数(负数表示反方向)
   zhuansuR =FTM_QUAD_get(FTM2);          //获取FTM 正交解码 的脉冲数(负数表示反方向)
//   zhuansuR =(int)(1.1*zhuansuR);
   FTM_QUAD_clean(FTM1);
   FTM_QUAD_clean(FTM2);
//   if(acc_t>10)
//   var[3]= zhuansuL;
//   var[4]= zhuansuR;

   SpeedControl();
   hundred_t=0;
  }
 // var[5]= GYRO_Z;
  
//  if(stop_flag>=1)
//  {
//    while(1)
//    {
//      FTM_PWM_Duty(FTM0, FTM_CH0,0);
//      FTM_PWM_Duty(FTM0, FTM_CH1,0);
//      FTM_PWM_Duty(FTM0, FTM_CH2,0);
//      FTM_PWM_Duty(FTM0, FTM_CH3,0); 
//    }
//  }

//  if(gpio_get(PTE0)==0)
//  {
//    stop_flag=1;
//  }
//  if((stop_flag==1)&&(gpio_get(PTE0)==1))
//  {
//    stop_flag=2;  
//  }
   if((stop_flag==1)&&(gpio_get(PTE1)==0))
  {     
     while(1)
     {
       FTM_PWM_Duty(FTM0, FTM_CH0,0);
       FTM_PWM_Duty(FTM0, FTM_CH1,0);
       FTM_PWM_Duty(FTM0, FTM_CH2,0);
       FTM_PWM_Duty(FTM0, FTM_CH3,0); 
     }
  }
  
  
   PIT_Flag_Clear(PIT0);       //清中断标志位  

   //pid_bal();

  /*
    FTM_PWM_Duty(FTM0, FTM_CH0,0);
    FTM_PWM_Duty(FTM0, FTM_CH1,0);

    FTM_PWM_Duty(FTM0, FTM_CH2,110);
    FTM_PWM_Duty(FTM0, FTM_CH3,0);
*/
    
   //vcan_sendware((uint8_t *)var, sizeof(var));
 /*     
   if(Flag_Start)
     Counter_Start++;
   if(Counter_Start > 5000)
     Flag_Start = 0;
   
   if(Flag_Stop)
     Counter_Stop++;
   if(Counter_Stop > 200)
   {
     Flag_Stop   = 0;
     Flag_Stop_F = 1;
   }
   

   if(Flag_Slope)
   {
     gpio_set(PTB20,0);
     Counter_Slope++;
   }
   if(Counter_Slope > 2000)
   {
     gpio_set(PTB20,1);
     Flag_Slope    = 0;
     Counter_Slope = 0;
   }
   */
}

void PORTE_IRQHandler(void)
{

#if 1       // 条件编译，两种方法可供选择

    uint8  n = 0;    //引脚号
    n = 1;
    if(PORTE_ISFR & (1 << n))           //PTD7 触发中断
    {
        PORTD_ISFR  = (1 << n);        //写1清中断标志位

        /*  以下为用户任务  */
	//DELAY_US(10);
	//stop_flag++;
	if(abs(pos_error)<=50)
	{
	  while(1)
	  {
	    FTM_PWM_Duty(FTM0, FTM_CH0,0);
            FTM_PWM_Duty(FTM0, FTM_CH1,0);
            FTM_PWM_Duty(FTM0, FTM_CH2,0);
            FTM_PWM_Duty(FTM0, FTM_CH3,0);
	  }
	}

        /*  以上为用户任务  */
    }
#else
    PORT_FUNC(E,1,key_handler);
#endif
}
//暂时搁置dma
/*
void PORTE_IRQHandler()
{
  if(PORTE_ISFR & (1<<0))
  {
    PORTE_ISFR = (1<<0);
    if(!(Flag_Start||Flag_Slope))
      Flag_Stop = 1;
  }
}
*/
