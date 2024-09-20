/*
 * File:   Spi_master.
 */


#include <xc.h>

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#define _XTAL_FREQ 20000000

void SPI_Slave_Init(void)
{
    TRISC3 =0; //SCK
    TRISC5 =0; //SDO
    TRISC4 =1;  //SDI
    TRISA5=0;  //SS 
    TRISA4=1; // for take input
    //configure SPI module
    SSPSTAT =0X40;
    SSPCON =0X20;
}



unsigned char SPI_Slave_Read(void)
{
    while(!SSPIF);
    SSPIF =0;
    return SSPBUF;
}

void SPI_Slave_Write(unsigned char data)
{
    SSPBUF =data;
    while(!SSPIF);
        SSPIF=0;  
}

void send_Str(unsigned char *s)
{
    while(*s)
    {
        SPI_Slave_Write(*s++);
    }
}
void main(void) {
   
    SPI_Slave_Init();
    while(1)
    {
     //SPI_Slave_Write(0xFF);
      /* __delay_ms(2000);
         SPI_Slave_Write(0x00);
        //unsigned char receved_data =SPI_Slave_Read();
        __delay_ms(2000);
        send_Str("hello");*/
        __delay_ms(1000);
        
        if(PORTAbits.RA4==0)
        {
            SPI_Slave_Write(0);
        }
        if(PORTAbits.RA4==1)
        {
            SPI_Slave_Write(1);
        }
    }
    //return;
}
