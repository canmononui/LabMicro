#include "Includes.h"
#include <intrins.h>
#include <absacc.h>

unsigned char Hour[2];
unsigned char Min[2];
unsigned char Sec[2];
unsigned char H;
unsigned char M;
unsigned char S	;
unsigned char KEY_DATA;
unsigned char alarm1[2];
unsigned char alarm2[2];
unsigned char alarm3[2];

void dmsec(unsigned int count2)
{
TMOD = (TMOD & 0xF0) | 0x01;/*Set T/C0 Mode*/
TR0=1;
while (count2)
{if (TF0==1)
{TR0=0; /* Stop Timer 0*/
TF0=0;
count2--;
TH0 = 0xEC; /* Load Timer withFFFFH-5000 */
TL0 = 0x77;
TR0 = 1; /* Start Timer 0*/
}
}
}

unsigned char get_key(void)	
{	
	RowA = 0; RowB = 1; RowC = 1; RowD = 1; 	//Test Row A

	if (C1 == 0) { delay(10000); while (C1==0); return 7; }
	if (C2 == 0) { delay(10000); while (C2==0); return 8; }
	if (C3 == 0) { delay(10000); while (C3==0); return 9; }

	RowA = 1; RowB = 0; RowC = 1; RowD = 1; 	//Test Row B

	if (C1 == 0) { delay(10000); while (C1==0); return 4; }
	if (C2 == 0) { delay(10000); while (C2==0); return 5; }
	if (C3 == 0) { delay(10000); while (C3==0); return 6; }
	
	RowA = 1; RowB = 1; RowC = 0; RowD = 1; 	//Test Row C

	if (C1 == 0) { delay(10000); while (C1==0); return 1; }
	if (C2 == 0) { delay(10000); while (C2==0); return 2; }
	if (C3 == 0) { delay(10000); while (C3==0); return 3; }
	
	RowA = 1; RowB = 1; RowC = 1; RowD = 0; 	//Test Row D

	if (C1 == 0) { delay(10000); while (C1==0); return 10; }
	if (C2 == 0) { delay(10000); while (C2==0); return 11; }
	if (C3 == 0) { delay(10000); while (C3==0); return 12; }

	return 0xff;           	// Means no key has been pressed
}         


void Check_Set_Time(void)
{
	KEY_DATA = get_key();
	if(KEY_DATA =='*')
	{
		Display_Set_Time();
		H = ((((Hour[0]<<1)&0x0F)>>1)*10)|((((Hour[1]<<1)&0x0F)>>1));
		M = ((((Min[0]<<1)&0x0F)>>1)*10)|((((Min[1]<<1)&0x0F)>>1));
		S = ((((Sec[0]<<1)&0x0F)>>1)*10)|((((Sec[1]<<1)&0x0F)>>1));
		delay(65000);
		InitLCD();	// Initialize LCD	
		InitI2C();	// Initialize i2c pins
		Set_DS1307_RTC_Time(AM_Time, H, M, S);
	}
	
	
	
}

char Check_Key(void)
{	
	char k = 'n';
	while(1)
		{	
			k = get_key();
			delay(10000);
			if(k != 'n' && k != '*')
			{break;}
			
		}
	return k;
}

void Show_LCD(void)
{
 			WriteDataToLCD(' ');
			Hour[0] = Check_Key();
			WriteDataToLCD(Hour[0]);
			Hour[1] = Check_Key();
			WriteDataToLCD(Hour[1]);
			WriteDataToLCD(':');
			Min[0] = Check_Key();
			WriteDataToLCD(Min[0]);
			Min[1] = Check_Key();
			WriteDataToLCD(Min[1]);
			WriteDataToLCD(':');
			Sec[0] = Check_Key();
			WriteDataToLCD(Sec[0]);
			Sec[1] = Check_Key();			   
			WriteDataToLCD(Sec[1]);
}

void Display_Set_Time(void)
{
			WriteCommandToLCD(0xc0);
			WriteStringToLCD("SET_TIM");
			Show_LCD();
			
}

