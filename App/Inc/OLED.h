#ifndef __OLED_H
#define __OLED_H

#include "common.h"
#include "mk60_gpio.h"

#define byte unsigned char

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

#define PIN_SCL PTC10
#define PIN_SDA PTC11

extern void OLED_Init(void);
extern void OLED_Fill(unsigned char bmp_dat);
extern void OLED_Set_Pos(unsigned char x, unsigned char y);
extern void OLED_WrDat(unsigned char IIC_Data);
extern void Print6x8int(uint8 x,uint8 y,int n);
extern void OLED_P6x8Str(byte x,byte y,byte ch[]);

#endif
