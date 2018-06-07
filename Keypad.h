#ifndef __KEY_H
#define __KEY_H

sbit RowA = P2^2;     //RowA
sbit RowB = P2^1;     //RowB
sbit RowC = P2^0;     //RowC
sbit RowD = P2^3;     //RowD
			 
sbit C1   = P2^4;     //Column1
sbit C2   = P2^5;     //Column2
sbit C3   = P2^6;     //Column3


void Check_Set_Time(void);
char Check_Key(void);
void Display_Set_Time(void);
void Show_LCD(void);
void dmsec(unsigned int);
unsigned char get_key(void);
#endif