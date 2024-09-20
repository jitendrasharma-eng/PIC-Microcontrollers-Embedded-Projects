/*
 * File:   Spi_slave.c
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
    TRISC3 =1; //SCK
    TRISC5 =0; //SDO
    TRISC4 =1;  //SDI
    TRISA5=1;  //SS 
    //configure SPI module
    SSPSTAT =0X40;
    SSPCON =0X24;
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

void main(void) {
    TRISB = 0x00;
    PORTB=0x00;
    SPI_Slave_Init();
    while(1)
    {
       //SPI_Slave_Write(0xFA);
        unsigned char receved_data =SPI_Slave_Read();
        //PORTB =receved_data;
        if(receved_data==1)
        {
           PORTBbits.RB7=1; 
        }
        if(receved_data==0)
        {
            PORTBbits.RB7=0;
        }
       // SPI_Slave_Write(receved_data);
       // __delay_ms(1000);
    }
    //return;
}
