#include "include.h"

int strategy;
//************平衡部分*********************
float Gyro_Now;
int MPU6050;

float fDeltaValue;
uint16    MMA7361;
float angle_offset_vertical;

float g_fCarAngle;//39
float g_fGyroscopeAngleIntegral;

int speed_Start;

//************速度部分*********************

int vi_Ref,vi_FeedBack,vi_PreError,vi_PreDerror;
int error1,error_t,d_error;
int Actualduty,increduty;
float fp,fi,g_fintegral;
float I_speed;
//********************************************
int   g_nSpeedControlPeriod;
float g_fCarSpeed;
float SPEED_CONTROL_P=60,//50//15
      SPEED_CONTROL_I=0.15;//0.001//0.005;

float g_fSpeedControlOut;
float g_fSpeedControlOutOld,g_fSpeedControlOutNew;
float g_fSpeedControlIntegral;
//****************************************
int vi_Ref,vi_FeedBackL,vi_FeedBackR,vi_PreErrorL,vi_PreErrorR,vi_PreDerrorL,vi_PreDerrorR;
int errorL,errorR,d_errorL,d_errorR;
float I_speedL,I_speedR;

float g_fSpeedControlOutNewL,g_fSpeedControlOutOldL;
float g_fSpeedControlOutNewR,g_fSpeedControlOutOldR;
float g_fSpeedControlOutL,g_fSpeedControlOutR;  

//************转向部分*********************
float   pos_kp ; 
float   pos_kd ;

int midheng,midzhi;
int result;

int FTMMOT_L,FTMMOT_R;    
int FTMMOT;   

int last_turn0,last_turn1,last_turn2;
int pos_error,pos_derror,pos_preerror;
int pos_up,pos_ud,pos_feedback;

int xiedu;
//*****十字*******
char shizi_flag=0;
//*****直道*******
unsigned int zhidao_flag=0;
//************ad采集部分*********************
unsigned char      left_hou  ;
unsigned char      left_zhi  ;
unsigned char      left_heng ;
unsigned char      mid_heng  ;
unsigned char      mid_zhi   ;
unsigned char      right_heng;
unsigned char      right_zhi ;
unsigned char      right_hou ;

unsigned char  AD[8][5];
uint16  A_X[5];
int cha_zhi0=0,cha_zhi1=0,cha_zhi2=0,he_zhi0=0,he_zhi1=0,he_zhi2=0,last_turn=0;//差值基准



//*****************************************************************
int dianliu1,dianliu2;
/*uint16 value_buf0[7],value_buf1[7],value_buf2[7],
       value_buf3[7],value_buf4[7],value_buf5[7],
       value_buf6[7],value_buf7[7];*/
//uint16 ad_result[7],left_heng,right_heng,mid_heng,left_xie,right_xie,left_zhi,right_zhi;//存放ad值的数组
/*char codecoe[5][5]={{1,1,2,3,5},
          {5,1,1,2,3},
          {3,5,1,1,2},
          {2,3,5,1,1},
          {1,2,3,5,1}}; //设置权重
*/

//************************************************************************************************
int ad_get()
{
  
   char j,k,adtmp,count;
   for(count=0;count<5;count++)
      {
          AD[0][count]=adc_once(L_xie ,ADC_8bit);
          AD[1][count]=adc_once(L_zhi ,ADC_8bit);
          AD[2][count]=adc_once(L_heng,ADC_8bit);
          AD[3][count]=adc_once(R_heng,ADC_8bit);
          AD[4][count]=adc_once(R_zhi ,ADC_8bit);
          AD[5][count]=adc_once(R_xie ,ADC_8bit);
          A_X[count]  =adc_once(XOUT  ,ADC_12bit);
       }
  
   for(k=0;k<6;k++)
   {  
         for(j=0;j<4;j++)
          {
             if(AD[k][j]>AD[k][j+1]) 
             {
                adtmp=AD[k][j+1];
                AD[k][j+1]=AD[k][j];
                AD[k][j]=adtmp;
              }
           }
    }
   for(k=1;k<5;k++)
   {
     A_X[0]+=A_X[k];
   }
    MMA7361=A_X[0]/5;

      left_heng  =(AD[1][2]-22)*150/(reference1-22);
      left_zhi   =(AD[2][2]-22)*150/(reference2-22);
      left_hou   =(AD[0][2]-22)*150/(reference1-22);
      right_hou  =(AD[5][2]-22)*150/(reference1-22);
      right_zhi  =(AD[3][2]-22)*150/(reference2-22);
      right_heng =(AD[4][2]-22)*150/(reference1-22);
      
//      dianliu1=adc_once(ADC0_DM1  ,ADC_12bit);
//      dianliu2=adc_once(ADC0_SE10  ,ADC_12bit);
      if (strategy==8)
      {
      left_heng  =AD[1][2];
      left_zhi   =AD[2][2];
      left_hou   =AD[0][2];
      right_hou  =AD[5][2];
      right_zhi  =AD[3][2];
      right_heng =AD[4][2];
      }
      cha_zhi0=left_heng-right_heng;
      he_zhi0 =left_heng+right_heng;
      
      cha_zhi1=left_zhi-right_zhi;
      he_zhi1 =left_zhi+right_zhi;
      
      cha_zhi2=left_hou-right_hou;
      he_zhi2 =left_hou+right_hou;
      return 0;
                                     
}
//******************************************************************************************************
int position()
{
  int pos_flag;
//*******************2m***************************
//   pos_flag=right_hou/10;
//   switch(pos_flag)
//   {
//       case 0:
//       case 1:
//        pos_kp=36;
//        break;
//       
//       case 2:
//       case 3:
//       
//         pos_kp=36;
//        break;
//        
//       case 4:
//       case 5:
//       
//         pos_kp=36;
//        break;
//        
//       case 6:
//      
//         pos_kp=36;
//         break;
//       case 7:
//     
//         pos_kp=36;
//        break;
//        
//       case 8:
//       case 9:
// 
//         pos_kp=36;
//        break;
//       
//       default:
//          pos_kp=36;
//       break;
//   }
//  result=(int)(((cha_zhi0*100)+(cha_zhi1*100))/(he_zhi0));
//**********************************************
   pos_flag=right_hou/10;
   switch(pos_flag)
   {
       case 0:
       case 1:
        pos_kp=24;
        break;
       
       case 2:
       case 3:
       
         pos_kp=23;
        break;
        
       case 4:
       case 5:
       
         pos_kp=23;
        break;
        
       case 6:
      
         pos_kp=23;
         break;
       case 7:
     
         pos_kp=23;
        break;
        
       case 8:
       case 9:
 
         pos_kp=22;
        break;
        
         case 10:
       case 11:
 
         pos_kp=22;
        break;
        
         case 12:
           pos_kp=22;
           break;
           
       case 13:
 
         pos_kp=21;
        break;
       
        case 14:
 
         pos_kp=20;
        break;
       default:
          pos_kp=20;
       break;
   }
   
    result=(int)(((cha_zhi0*100)+(cha_zhi1*100))/(he_zhi0));

  //result=(int)(cha_zhi0*130/(he_zhi0));//(int)(((cha_zhi0*130)+(cha_zhi1*70))/(he_zhi0));

  while((left_heng<5)&&(left_zhi<5)&&(right_zhi<5)&&(right_heng<5))
  {
       FTM_PWM_Duty(FTM0, FTM_CH0,0);
       FTM_PWM_Duty(FTM0, FTM_CH1,0);
       FTM_PWM_Duty(FTM0, FTM_CH2,0);
       FTM_PWM_Duty(FTM0, FTM_CH3,0);

//      left_heng  =(adc_once(R_zhi ,ADC_8bit)-24)*100/(reference-24);
//      left_zhi   =(adc_once(L_heng,ADC_8bit)-25)*100/(reference-25);
//      right_zhi  =(adc_once(R_heng,ADC_8bit)-24)*100/(reference-24);
//      right_heng =(adc_once(L_zhi ,ADC_8bit)-24)*100/(reference-24);
  }
//   result=cha_zhi2*100/he_zhi2;
//  pos_kp=20;
  last_turn=result;
//  result=(int)(result*0.4+last_turn0*0.3+last_turn1*0.2+last_turn2*0.1);
//  last_turn0=result;
//  last_turn1=last_turn0;
//  last_turn2=last_turn1;
  return result; 
}

//void SpeedControl(void) //加速部分
//{
//  /* if(Flag_Stop_F)
//   {
//     vi_Ref = -1;
//   }
//   else*/
//   vi_Ref=(int)(plan.CAR_SPEED_SETfDelta);//fast[spchoose];
//   vi_FeedBackL=zhuansuL/5;//5
//   vi_FeedBackR=zhuansuR/5;//5
//   errorL=vi_Ref-vi_FeedBackL;
//   errorR=vi_Ref-vi_FeedBackR;
//   d_errorL=errorL-vi_PreErrorL;
//   d_errorR=errorR-vi_PreErrorR;
//
//  
//  vi_PreDerrorL=vi_PreErrorL;
//  vi_PreDerrorR=vi_PreErrorR;
//  vi_PreErrorL=errorL;
//  vi_PreErrorR=errorR;
//  I_speedL=plan.ACC_Ki*errorL;
//  I_speedR=plan.ACC_Ki*errorR;
////  if(abs((int)I_speed)>50)
////    I_speed=(int)(abs(error1)/error1*50);
////  if((error1>15)|(error1<-15))
////    I_speed=0;
//  g_fSpeedControlOutOldL = g_fSpeedControlOutNewL;
//  g_fSpeedControlOutNewL+=(plan.ACC_Kp*d_errorL+I_speedL+plan.ACC_Kd*(errorL-2*vi_PreErrorL+vi_PreDerrorL));
//  g_fSpeedControlOutOldR = g_fSpeedControlOutNewR;
//  g_fSpeedControlOutNewR+=(plan.ACC_Kp*d_errorR+I_speedR+plan.ACC_Kd*(errorR-2*vi_PreErrorR+vi_PreDerrorR));
//  g_nSpeedControlPeriod=0;
//}

void SpeedControl(void) //加速部分
{
  /* if(Flag_Stop_F)
   {
     vi_Ref = -1;
   }
   else*/
   vi_Ref=(int)(plan.CAR_SPEED_SETfDelta);//fast[spchoose];
   vi_FeedBack=(zhuansuL+zhuansuR)/2;
//   if(vi_FeedBack<70)
//   vi_Ref=100;
//   else if(vi_FeedBack<150)
//   vi_Ref=180;
//   else if(vi_FeedBack<230)
//   vi_Ref=260;

   error1=vi_Ref-vi_FeedBack;
//   if(abs(error1)>100)
//     error1=(abs(error1)/error1)*100;
   d_error=error1-vi_PreError;

  
  vi_PreDerror=vi_PreError;
  vi_PreError=error1;
  I_speed=plan.ACC_Ki*error1;
//  if(abs((int)I_speed)>200)
//    I_speed=(int)(abs(error1)/error1*200);
//  if((error1>20)|(error1<-20))
//    I_speed=0;
  I_speed=(plan.ACC_Kp*d_error+I_speed+plan.ACC_Kd*(error1-2*vi_PreError+vi_PreDerror));
//   if(abs((int)(I_speed))>150)
//     I_speed=(abs((int)(I_speed))/(int)(I_speed))*150;
  g_fSpeedControlOutOld = g_fSpeedControlOutNew;
  g_fSpeedControlOutNew+=I_speed;
//  if ((he_zhi0<140)&&(right_hou<90))
//  {
//    g_fSpeedControlOutNew=0;
//  }
  g_nSpeedControlPeriod=0;
}


//void SpeedControl(void) 
//{
//  float fDelta;
//  float fP, fI;
//  g_fCarSpeed = (zhuansuL+zhuansuR)/2;
//
//
//  fDelta = 0 - g_fCarSpeed;
//
//  fP = fDelta * SPEED_CONTROL_P;
//  fI = fDelta * SPEED_CONTROL_I;
//
//  g_fSpeedControlIntegral += fI; 
//  g_fSpeedControlOutOld = g_fSpeedControlOutNew;
//
//  g_fSpeedControlOutNew = fP + g_fSpeedControlIntegral;
//  g_nSpeedControlPeriod=0;
//}

int pid_acc(void) 
{
  float fValue;
  fValue = g_fSpeedControlOutNew - g_fSpeedControlOutOld;
  g_fSpeedControlOut = fValue * (++g_nSpeedControlPeriod)/10 + g_fSpeedControlOutOld;
  return (int)g_fSpeedControlOut;
}
//
//int pid_acc(void) 
//{
//  float fValueL,fValueR;
//  fValueL = g_fSpeedControlOutNewL - g_fSpeedControlOutOldL;
//  fValueR = g_fSpeedControlOutNewR - g_fSpeedControlOutOldR;
//  g_fSpeedControlOutL = fValueL * (++g_nSpeedControlPeriod)/10 + g_fSpeedControlOutOldL;
//  g_fSpeedControlOutR = fValueR * (g_nSpeedControlPeriod)/10 + g_fSpeedControlOutOldR;
//  FTMMOT_L-=g_fSpeedControlOutL;
//  FTMMOT_R-=g_fSpeedControlOutR;
////  FTMMOT_L=(int)g_fSpeedControlOutL;
////  FTMMOT_R=(int)g_fSpeedControlOutR;
//  return 0;
//}

int pid_turn()//转向部分
{ 
  
  pos_feedback=position();//位置
  pos_error=pos_ref-pos_feedback;

  //pos_derror=pos_error-pos_preerror;
  //pos_preerror= pos_error;
  pos_kd=GYRO_Z*plan.turn_D;//0.026
//
//   if((pos_kd>-150)&&(pos_kd<150))
//    pos_kd=0.01*GYRO_Z;

//  if((pos_kd>0)&&(pos_kd<5))//15
//    pos_kd=5;
//  else if((pos_kd>-5)&&(pos_kd<0))
//    pos_kd=-5;
//   if((pos_kd>1000))
//    pos_kd=1000;
//  if((pos_kd<-1000))
//    pos_kd=-1000;
  //var[5]=GYRO_Z;
    pos_up=(int)(pos_kp*pos_error);
    pos_ud=(int)(pos_kd);
  if(pos_feedback<0)
  {  
    FTMMOT_L=-(pos_up+pos_ud)-deadval_R;    
    FTMMOT_R=-FTMMOT_L; //-FTMMOT_L;   //差速方案
  }
  else
    {  
    FTMMOT_R=(pos_up+pos_ud)-deadval_L;    
    FTMMOT_L=-FTMMOT_R;    
  }
  return 0;
}


int pid_bal()
 {
   /*******************ad计算*******************************/
  MPU6050 = - GYRO_X;

  Gyro_Now = ( MPU6050 - GYRO_VAL) * Gyro_ratio ;//131
  //陀螺仪采集到的角速度归一化
  angle_offset_vertical = (MMA7361 - MMA7361_vertical)* MMA7361_ratio-plan.Angel_set;
  //将加速度计采集到的角度归一化，归一化到 0~90°

  if(angle_offset_vertical > 90)angle_offset_vertical = 90;
  //防止加速度角度溢出
  if(angle_offset_vertical < -90)angle_offset_vertical = -90;
 
 //计算融合后的角度
  g_fCarAngle = g_fGyroscopeAngleIntegral; //最终融合角度
  fDeltaValue = (angle_offset_vertical - g_fCarAngle) / GRAVITY_ADJUST_TIME_CONSTANT;
  //时间系数矫正
  g_fGyroscopeAngleIntegral += (Gyro_Now+ fDeltaValue) * DT; //融合角度
  /****************************速度计算***************************/
  speed_Start =(int)(g_fCarAngle * P_ANGLE + Gyro_Now * D_ANGLE) ;
  //直立时所要的速度
  //P_ANGLE P_GYRO 宏定义 直立所需要的 PD 参数
  

//  var[0]= Gyro_Now;
//  var[1]= angle_offset_vertical;
//  var[2]= g_fCarAngle;
  
//  var[0]= right_hou/10;
//  var[1]= pos_kp; 
//  var[2]= pos_error;
//  //vcan_sendware((uint8_t *)var, sizeof(var));
  
      var[0]= plan.CAR_SPEED_SETfDelta;
      var[1]= vi_FeedBack; 
      var[2]= I_speed;
 
  return speed_Start;
  }

int FTM_mot()
{
//  pid_turn();
//  FTMMOT   =pid_bal()-pid_acc();
  //FTMMOT_L+=FTMMOT;
  //FTMMOT_R+=FTMMOT;
  FTMMOT   =speed_Start;
  FTMMOT -=(int)g_fSpeedControlOut;//  FTMMOT +=g_fSpeedControlOut;
  FTMMOT_L+=FTMMOT;
  FTMMOT_R+=FTMMOT;
//  FTMMOT_L=(int)(0.9*FTMMOT_L);//0.94
  
 //FTMMOT_R=(int)(1* FTMMOT_R);
//   FTMMOT   =(int)g_fSpeedControlOut;
//   FTMMOT_L=FTMMOT;
//   FTMMOT_R=FTMMOT;
//   FTMMOT_L=150;
//   FTMMOT_R=150;

  
  if(FTMMOT_L>=dutymax) FTMMOT_L=dutymax;
  if(FTMMOT_L<=-dutymax) FTMMOT_L=-dutymax;
  if(FTMMOT_R>=dutymax) FTMMOT_R=dutymax;
  if(FTMMOT_R<=-dutymax) FTMMOT_R=-dutymax;
  
  if(FTMMOT_L>0)
  {
    FTM_PWM_Duty(FTM0, FTM_CH0,0);
    FTM_PWM_Duty(FTM0, FTM_CH1,FTMMOT_L);
  }
  else
  {
    FTM_PWM_Duty(FTM0, FTM_CH0,-FTMMOT_L);
    FTM_PWM_Duty(FTM0, FTM_CH1,0);
  }
  
  
  
  if(FTMMOT_R>0)
  {
    FTM_PWM_Duty(FTM0, FTM_CH2,FTMMOT_R);
    FTM_PWM_Duty(FTM0, FTM_CH3,0);
  }
  else
  {
    FTM_PWM_Duty(FTM0, FTM_CH2,0);
    FTM_PWM_Duty(FTM0, FTM_CH3,-FTMMOT_R);
  }

  return 0;
}
//******************************************************************************************************

int system_init()
{
  FTM_PWM_init(FTM0, FTM_CH0,20*1000,0);        //（未完成）初始化 FTM PWM ，使用 FTM0_CH，频率为200k ，占空比为 30 / FTM0_PRECISON                                          
  FTM_PWM_init(FTM0, FTM_CH1,20*1000,0);
  FTM_PWM_init(FTM0, FTM_CH2,20*1000,0);        //（未完成）初始化 FTM PWM ，使用 FTM0_CH，频率为200k ，占空比为 30 / FTM0_PRECISON                                                  
  FTM_PWM_init(FTM0, FTM_CH3,20*1000,0);
  
  
  
   FTM_QUAD_Init(FTM1);                        
   port_init_NoALT(FTM1_QDPHA,PULLUP);       
   port_init_NoALT(FTM1_QDPHB,PULLUP);
   
   FTM_QUAD_Init(FTM2);   
   port_init_NoALT(FTM2_QDPHA,PULLUP);       
   port_init_NoALT(FTM2_QDPHB,PULLUP);
                        
  
  adc_init(L_xie );  
  adc_init(L_heng); 
  adc_init(L_zhi ); 
  //adc_init(M_heng); 
  //adc_init(M_zhi ); 
  adc_init(R_zhi );
  adc_init(R_heng); 
  adc_init(R_xie ); 
  adc_init (XOUT); //MMA7361 X 轴
  //adc_init (ZOUT); //MMA7361 X 轴
  
//  adc_init(ADC0_DM1); 
//  adc_init(ADC0_SE10); 
  /*
   gpio_init(PTE25,GPI,0);
   gpio_init(PTE26,GPO,0);
   gpio_init(PTE27,GPI,0);
   gpio_init(PTE28,GPO,0);
   

     
    gpio_init(PTD0,GPI,1);
    gpio_init(PTD1,GPI,1);
        
    gpio_init(PTB20,GPO,1);
    gpio_init(PTB21,GPO,1);
    gpio_init(PTB22,GPO,1);
    gpio_init(PTB23,GPO,1);
*/
    gpio_init(PTA4,GPO,1);
    
    gpio_init(PTA24,GPI,1);
    gpio_init(PTA27,GPI,1);
    gpio_init(PTA26,GPI,1);
    gpio_init(PTA29,GPI,1);
    
       
    gpio_init(PTE0, GPO, 1);
    gpio_init(PTE2, GPO, 1);
    gpio_init(PTE3, GPO, 1);
    gpio_init(PTE4, GPO, 1);
    gpio_init(PTE5, GPO, 1);
    
    gpio_init(PTE1, GPI, 1);
    port_init_NoALT(PTE1, PULLUP);

    //port_init(PTE1, ALT1 | IRQ_FALLING | PULLUP );          //初始化 PTD7 管脚，复用功能为GPIO ，下降沿触发中断，上拉电阻

    //set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler);    //设置PORTE的中断复位函数为 PORTE_IRQHandler
     
    //set_irq_priority;
    //NVIC_SetPriorityGrouping(0);
      
    while(!mpu6050_init());//检测mpu6050地址是否正确
   //i2c_init(I2C1,400 * 1000);
    OLED_Init(); //oled初始化
/*
    port_init(PTE0,ALT1|IRQ_ZERO|PULLUP);
    set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler);    			//设置 PORTE 的中断复位函数为 PORTE_VECTORn
    enable_irq(PORTE_IRQn);
    
    Flag_Start = 1;
    */ 
    
    pit_init_ms(PIT0,1);                                //初始化PIT0，定时时间为： 1ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //设置PIT0的中断服务函数为 PIT0_IRQHandler
    
  return 0;
  
}

void my_switch()
{
  if((gpio_get(PTA24)==1)&&(gpio_get(PTA27)==1)&&(gpio_get(PTA26)==1)&&(gpio_get(PTA29)==1))
  {
    strategy=1;
  }
  else if((gpio_get(PTA24)==0)&&(gpio_get(PTA27)==1)&&(gpio_get(PTA26)==1)&&(gpio_get(PTA29)==1))
  {
    strategy=2;
  }
  else if((gpio_get(PTA24)==1)&&(gpio_get(PTA27)==0)&&(gpio_get(PTA26)==1)&&(gpio_get(PTA29)==1))
  {
    strategy=3;
  }
  
  else if((gpio_get(PTA24)==1)&&(gpio_get(PTA27)==1)&&(gpio_get(PTA26)==0)&&(gpio_get(PTA29)==1))
  {
    strategy=4;
  }
  else if((gpio_get(PTA24)==1)&&(gpio_get(PTA27)==1)&&(gpio_get(PTA26)==1)&&(gpio_get(PTA29)==0))
  {
    strategy=5;
  }
  else if((gpio_get(PTA24)==0)&&(gpio_get(PTA27)==1)&&(gpio_get(PTA26)==1)&&(gpio_get(PTA29)==0))
  {
    strategy=6;
  }
  else if((gpio_get(PTA24)==0)&&(gpio_get(PTA27)==0)&&(gpio_get(PTA26)==1)&&(gpio_get(PTA29)==0))
  {
    strategy=7;
  }
  else if((gpio_get(PTA24)==0)&&(gpio_get(PTA27)==0)&&(gpio_get(PTA26)==0)&&(gpio_get(PTA29)==0))
  {
    strategy=8;
  }
}
