/*  Name     : main.c
 *  Purpose  : Main file for DS1307 RTC code for AT89C51.
 *  Author   : M.Saeed Yasin
 *  Date     : 06-11-12
 *  Website  : saeedsolutions.blogspot.com
 *  Revision : None
 */
#include "Includes.h"
unsigned char BUFF[4]={1,1,1,1},KE,st;
void changBUFF(unsigned	char level)
{
	unsigned int i;
	for(i=0;i<3;i++)
	{
		BUFF[i]=BUFF[i+1];
	}
	BUFF[3]= level;
}
unsigned char startlevel()
{
	unsigned char le[3]={0,0,0},i,max,c;
	for(i=0;i<4;i++)
	{
		if(BUFF[i]==1)
		{
			le[0]++;
		}
		else if(BUFF[i]==2)
		{
			le[1]++;
		}
		else if(BUFF[i]==3)
		{
			le[2]++;
		}
	}
	max=le[0];
	c=0;
	for(i=1;i<3;i++)
	{
		if(le[i]>max)
		{
			max=le[i];
			c=i;
		}
	}
	return (c+1);
}
// Main function
void main()
{	

 	InitLCD();	// Initialize LCD	
	InitI2C();	// Initialize i2c pins


	P1 = 0xff;
	P2 = 0xff;
	while (1)
 	{
		//WriteStringToLCD("aaa");
		// Display RTC time on first line of LCD
		//Check_Set_Time();// Display RTC date on second line of LCD
		//DisplayTimeToLCD(Get_DS1307_RTC_Time());		
 		KE = get_key();
		if (KE== 12){
			st=startlevel();
			if (st== 1){
				P1=0xfe;
				gotolcd(0x40);// Set Cursor Line-1
		 		
			}
			else if (st== 2){
				P1=0xfd;
				gotolcd(0x40);// Set Cursor Line-1
		 	
			}
			else if (st== 3){
				P1=0xfb;
				gotolcd(0x40);// Set Cursor Line-1
		 		
			}
			while(KE!=11)
			{
				DisplayTimeToLCD(Get_DS1307_RTC_Time());
				KE = get_key();
				if (KE== 1){
					P1=0xfe;
					gotolcd(0x40);// Set Cursor Line-1
		 			
					changBUFF(1);
					while(KE!=0xff)
					{
						KE = get_key();
						dmsec(30);
					}
				}
				else if (KE== 2){
					P1=0xfd;
					gotolcd(0x40);// Set Cursor Line-1
		 			
					changBUFF(2);
					while(KE!=0xff)
					{
						KE = get_key();
						dmsec(30);
					}
				}
				else if (KE== 3){
					P1=0xfb;
					gotolcd(0x40);// Set Cursor Line-1
		 			
					changBUFF(3);
					while(KE!=0xff)
					{
						KE = get_key();
						dmsec(30);
					}
				}
			}
			P1=0xff;
			ClearLCDScreen();
 		}
 	}//End of while  												
}
