/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,Ұ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
 *
 * @file       MK60_it.c
 * @brief      Ұ��K60 ƽ̨�жϸ�λ����
 * @author     Ұ��Ƽ�
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
   zhuansuL =-FTM_QUAD_get(FTM1);          //��ȡFTM �������� ��������(������ʾ������)
   zhuansuR =FTM_QUAD_get(FTM2);          //��ȡFTM �������� ��������(������ʾ������)
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
  
  
   PIT_Flag_Clear(PIT0);       //���жϱ�־λ  

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

#if 1       // �������룬���ַ����ɹ�ѡ��

    uint8  n = 0;    //���ź�
    n = 1;
    if(PORTE_ISFR & (1 << n))           //PTD7 �����ж�
    {
        PORTD_ISFR  = (1 << n);        //д1���жϱ�־λ

        /*  ����Ϊ�û�����  */
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

        /*  ����Ϊ�û�����  */
    }
#else
    PORT_FUNC(E,1,key_handler);
#endif
}
//��ʱ����dma
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
