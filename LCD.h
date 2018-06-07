#ifndef __LCD_H
#define __LCD_H

//*******************
//Pin description
/*
P2.4 to P2.7 is data bus
P1.0 is RS
P1.1 is E
*/
//********************

// Defines Pins
#define PORT_LCD P0
sbit RS = PORT_LCD^3;
sbit E  = PORT_LCD^1;

// Constants
#define E_Delay       250       

// Function Declarations
void InitLCD(void);
void WriteCommandToLCD(int);
void WriteDataToLCD(char);
void ClearLCDScreen(void);
void WriteStringToLCD(const char*);
void DisplayTimeToLCD(unsigned char*) ;
char busy_lcd(void);
void gotolcd(unsigned char);



#endif