#include "include.h"

//*************************启停车部分*****************************************
uint8 count_ad,Flag_Stop = 0,Flag_Start = 0,Flag_Stop_F = 0,Flag_Slope = 0;
uint16 Counter_Start = 0,Counter_Stop = 0,Counter_Slope = 0;

//*************************oled部分*****************************************
uint8 code[2][6] = {{0x00,0x02,0x0C,0x30,0x40,0x00},
{0x00,0x00,0x00,0x7E,0x00,0x00}};

//*************************归一化初值与编码器数值*****************************
int reference1=140,reference2=140;
int zhuansuL,zhuansuR;

//************虚拟示波器*********************
float  var[3];

//***********************编码器用结构体****************************************
date_speed plan;

//******************************************************************************
void main()
{
//  #if   MK60F15      
//
//    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));     /* set CP10 and CP11 Full Access */
//
//#endif
  //int t=0;
  system_init();
  my_switch();

//****************2m********************* 
//  plan.ACC_Kp=20;//30
//  plan.ACC_Ki=0;//0.001
//  plan.ACC_Kd=10;//15
//  
//  plan.Angel_set=26;//30
//  plan.CAR_SPEED_SETfDelta=120;//-100
//  
//  plan.turn_D=0.045;//0.05
//  
//  plan.pos_avr=20;//15
//  plan.pos_com=0.01;//0.03
//  plan.pos_up=24;//20
//  plan.pos_down=26;//23
  //zhilip=300;
//*************************************
  plan.ACC_Kp=23;//30//100
  plan.ACC_Ki=0.1;//0.001
  plan.ACC_Kd=0;//15
  
  plan.Angel_set=23;//25
  plan.CAR_SPEED_SETfDelta=0;//300 //-20
  
  plan.turn_D=0.12;//0.005//0.08
  
//  plan.pos_avr=20;//15
//  plan.pos_com=0.01;//0.03
//  plan.pos_up=24;//20
//  plan.pos_down=26;//23
//*************************************
    enable_irq (PIT0_IRQn);                                 //使能PIT0中断
    //enable_irq (PORTE_IRQn);

//  while(t<10)
//  {
//    reference+=adc_once(L_heng,ADC_8bit);   //获得归一化的参考值
//    t++;
//    DELAY_MS(100);
//  }
//  reference=reference/10;

   DELAY_MS(2000);
  
   plan.ACC_Kp=50;//30//100
   plan.ACC_Ki=0.001;//0.001
   plan.ACC_Kd=20;//15
  
   plan.CAR_SPEED_SETfDelta=60;//300 //-20   
   plan.Angel_set=50;
   
   DELAY_MS(1000);
   
   plan.Angel_set=22;
    
   DELAY_MS(700);
    
     
   if(strategy==1)
  {    
    plan.Angel_set=20;
    plan.ACC_Kp=30;//30//100
    plan.ACC_Ki=0.001;//0.001
    plan.CAR_SPEED_SETfDelta=35;//300 //-20  //55 //50 //57
    
  }
  
   else if(strategy==2)
  {
    plan.Angel_set=21;
    plan.ACC_Kp=30;//30//100
    plan.ACC_Ki=0.001;//0.001
    plan.CAR_SPEED_SETfDelta=35;//300 //-20  //55 //50 //57
  }
  else if(strategy==3)
  {
    plan.Angel_set=21;
    plan.ACC_Kp=30;//30//100
    plan.ACC_Ki=0.001;//0.001
    plan.CAR_SPEED_SETfDelta=45;//300 //-20  //55 //50 //57
  }
  else if(strategy==4)
  {    
    plan.Angel_set=22;
    plan.ACC_Kp=30;//30//100
    plan.ACC_Ki=0.001;//0.001
    plan.CAR_SPEED_SETfDelta=45;//300 //-20  //55 //50 //57
  }
  else if(strategy==5)
  {    
    plan.Angel_set=23;
    plan.ACC_Kp=30;//30//100
    plan.ACC_Ki=0.001;//0.001
    plan.CAR_SPEED_SETfDelta=50;//300 //-20  //55 //50 //57
    
  }
  else if(strategy==6)
  {    
    plan.Angel_set=24;
    plan.ACC_Kp=30;//30//100
    plan.ACC_Ki=0.001;//0.001
    plan.CAR_SPEED_SETfDelta=55;//300 //-20  //55 //50 //57    
  }
  else if(strategy==7)
  {    
    plan.Angel_set=25;
    plan.ACC_Kp=30;//30//100
    plan.ACC_Ki=0.001;//0.001
    plan.CAR_SPEED_SETfDelta=60;//300 //-20  //55 //50 //57
    
  }
  
   DELAY_MS(2000);
   //enable_irq(PORTE_IRQn);
   stop_flag=1;
   while(1)
  { 


//      var[0]= plan.CAR_SPEED_SETfDelta;
//      var[1]= vi_FeedBack; 
//      var[2]= I_speed;
     //vcan_sendware((uint8_t *)var, sizeof(var));    
    
      OLED_P6x8Str(0,0,"L -:");
      OLED_P6x8Str(0,1,"L l:");
      OLED_P6x8Str(0,2,"M -:");
      OLED_P6x8Str(0,3,"R l:");
      OLED_P6x8Str(0,4,"R -:");
      OLED_P6x8Str(0,5,"ZH:");
//      //OLED_P6x8Str(0,6,"R X:");
      
      Print6x8int(25,0,left_heng);          //英文字符串显示
      Print6x8int(25,1,left_zhi);          //英文字符串显示
      Print6x8int(25,2,right_hou);          //英文字符串显示
      Print6x8int(25,3,right_zhi);          //英文字符串显示
      Print6x8int(25,4,right_heng);          //英文字符串显示
      Print6x8int(25,5,g_fCarAngle);          //英文字符串显示
    //  Print6x8int(25,6,right_xie);          //英文字符串显示*/
//      Print6x8int(25,0,AD[1][2]);          //英文字符串显示
//      Print6x8int(25,1,AD[2][2]);          //英文字符串显示
//      Print6x8int(25,2,AD[5][2]);          //英文字符串显示
//      Print6x8int(25,3,AD[3][2]);          //英文字符串显示
//      Print6x8int(25,4,AD[4][2]);          //英文字符串显示
   //int a,b,c;
  /*  
   gpio_set(PTE28,1);
   systick_delay_us(10);
   gpio_set(PTE28,0);
   
   gpio_set(PTE26,1);
   systick_delay_us(10);
   gpio_set(PTE26,0);
  */
    //稍后使用
    //a=mpu6050_GYRO_X_data() ;
    //b=mpu6050_GYRO_Y_data() ;
    //c=mpu6050_GYRO_Z_data() ;
    //ad_get();

    //printf("%d,%d\n",zhuansuR,zhuansuL);//左右轮转速
   //printf("%d,%d,%d,%d,%d,%d\n",left_hou,left_heng,left_zhi,right_zhi,right_heng,right_hou);//电感值
   //printf("%d,%d\n",result,(pos_up+pos_ud));//转角输出
    //printf("%d\n",GYRO_Z);//转向陀螺仪输出
    
    //DELAY_MS(100);
    //pid_bal();
     //vcan_sendware((uint8_t *)var, sizeof(var));
  }

}


//************************************************************************************************

/*
 unsigned int wafilter(char k)   //k表示第几个电感
 {
    char count;
    int sum=0; 
    switch(k)
        {
        case 0:

           for(count=0;count<5;count++)
              value_buf0[count]=adc_once(ADC1_SE8,ADC_8bit);
              
           for(count=0;count<5;count++) sum+=value_buf0[count]*codecoe[count_ad][count];
           break;
        case 1:
       
              for(count=0;count<5;count++)
                value_buf1[count]=adc_once(ADC1_SE9,ADC_8bit);
             
             for(count=0;count<5;count++) sum+=value_buf1[count]*codecoe[count_ad][count];
            break;
        case 2:
     
              for(count=0;count<5;count++)
                value_buf2[count]=adc_once(ADC1_SE10,ADC_8bit);
              
            for(count=0;count<5;count++) sum+=value_buf2[count]*codecoe[count_ad][count];
           break;
        case 3:
        
              for(count=0;count<5;count++)
                value_buf3[count]=adc_once(ADC1_SE11,ADC_8bit);
             
             for(count=0;count<5;count++) sum+=value_buf3[count]*codecoe[count_ad][count];
            break;           
        case 4:
        
              for(count=0;count<5;count++)
                value_buf4[count]=adc_once(ADC1_SE12,ADC_8bit);
           
             for(count=0;count<5;count++) sum+=value_buf4[count]*codecoe[count_ad][count];
            break;           
        case 5:
    
              for(count=0;count<5;count++)
                value_buf5[count]=adc_once(ADC1_SE13,ADC_8bit);
             
            for(count=0;count<5;count++) sum+=value_buf5[count]*codecoe[count_ad][count];
            break; 
         case 6:
     
              for(count=0;count<5;count++)
                value_buf6[count]=adc_once(ADC1_SE14,ADC_8bit);
            
             for(count=0;count<5;count++) sum+=value_buf6[count]*codecoe[count_ad][count];
            count_ad++;
            if(count_ad>4)
                count_ad=0;
            break; 
    } 
    return(uint16)(sum/12);//加权递推均值法滤波
 }//可考虑用dma优化
*/
//*****************************************************************************************************
