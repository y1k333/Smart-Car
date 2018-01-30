#include "include.h"
#include "OlED.h"
#include "CodeTable.h"

void IIC_Start()
{
   gpio_set(PIN_SCL, 1);		
   gpio_set(PIN_SDA, 1);
   gpio_set(PIN_SDA, 0);
   gpio_set(PIN_SCL, 0);
}

void IIC_Stop()
{
   gpio_set(PIN_SCL, 0);
   gpio_set(PIN_SDA, 0);
   gpio_set(PIN_SCL, 1);
   gpio_set(PIN_SDA, 1);
}

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(IIC_Byte & 0x80)
			gpio_set(PIN_SDA, 1);
		else
			gpio_set(PIN_SDA, 0);
		gpio_set(PIN_SCL, 1);
		gpio_set(PIN_SCL, 0);
		IIC_Byte<<=1;
	}
	gpio_set(PIN_SDA, 1);
	gpio_set(PIN_SCL, 1);
	gpio_set(PIN_SCL, 0);
}

void OLED_WrDat(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	Write_IIC_Byte(0x40);			//write data
	Write_IIC_Byte(IIC_Data);
	IIC_Stop();
}

void OLED_WrCmd(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);            //Slave address,SA0=0
	Write_IIC_Byte(0x00);			//write command
	Write_IIC_Byte(IIC_Command);
	IIC_Stop();
}

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 

void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}
void OLED_CLS(void)
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
	}
}

void OLED_Init(void)
{
  gpio_init(PIN_SCL, GPO, 1);		
  gpio_init(PIN_SDA, GPO, 1);
  systick_delay_ms(500);//3?那??‘???～米??車那㊣o邦??辰a㏒?
  OLED_WrCmd(0xae);//--turn off oled panel
  OLED_WrCmd(0x00);//---set low column address
  OLED_WrCmd(0x10);//---set high column address
  OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  OLED_WrCmd(0x81);//--set contrast control register
  OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
  OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0℅車車辰﹞∩?? 0xa1?y3㏒
  OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0谷???﹞∩?? 0xc8?y3㏒
  OLED_WrCmd(0xa6);//--set normal display
  OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
  OLED_WrCmd(0x3f);//--1/64 duty
  OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  OLED_WrCmd(0x00);//-not offset
  OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
  OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  OLED_WrCmd(0xd9);//--set pre-charge period
  OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  OLED_WrCmd(0xda);//--set com pins hardware configuration
  OLED_WrCmd(0x12);
  OLED_WrCmd(0xdb);//--set vcomh
  OLED_WrCmd(0x40);//Set VCOM Deselect Level
  OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  OLED_WrCmd(0x02);//
  OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
  OLED_WrCmd(0x14);//--set(0x10) disable
  OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
  OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
  OLED_WrCmd(0xaf);//--turn on oled panel
  OLED_Fill(0x00); //3?那????芍
  OLED_Set_Pos(0,0);
} 

void OLED_P6x8Str(byte x,byte y,byte ch[])
{
  byte c=0,i=0,j=0;      
  while (ch[j]!='\0')
  {    
    c =ch[j]-32;
    if(x>126){x=0;y++;}
    OLED_Set_Pos(x,y);    
  	for(i=0;i<6;i++)     
  	  OLED_WrDat(F6x8[c][i]);  
  	x+=6;
  	j++;
  }
}
void OLED_P6x8Ch(uint8 x,uint8 y,char ch)
{
  uint8 i=0;
    OLED_Set_Pos(x,y);    
  	for(i=0;i<6;i++)     
  	  OLED_WrDat(F6x8[ch-32][i]);
}
void Print6x8int(uint8 x,uint8 y,int n)
{

	uint16 c=10000;
	uint8 i=0,j,k=0;      
	if(n<0)
        {
          OLED_P6x8Ch(x, y, '-');
          n=-n;x+=6;
        }
	
	for(i=0;i<5;i++)
	{
		j=n/c%10;
		if((j!=0)||(k==1))
		{
			//OLED_P6x8(x,y,j+48);
                        OLED_P6x8Ch(x, y, j+48);
			x+=6;
			k=1;
		}
		c/=10;
		
	}
        OLED_P6x8Str(x, y, "   ");
	//OLED_P6x8Str(x,y,"   ");
}
