#include <xc.h>

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void ser_init();
void tx(unsigned char);
unsigned char rx();
void txstr(unsigned char*);

void main(void) {
    TRISC6 = 0;   //OUTPUT(TX)
    TRISC7 = 1;   //INPUT(RX)
    ser_init();
    txstr("Hello world");
    
    while(1)
    {
        tx(rx());  // Echo received character
    }
    return;
}

void ser_init() {
    TXSTA = 0x20;         // TXEN=1, Asynchronous mode, 8-bit, BRGH=0 (low speed)
    RCSTA = 0b10010000;   // SPEN=1 (Serial port enabled), CREN=1 (Enable reception)
    SPBRG = 17;           // Baud rate set for 9600, assuming 11.0592 MHz clock
}

void tx(unsigned char a)
{
    while(!TXSTAbits.TRMT);  // Wait until TSR (Transmit Shift Register) is empty
    TXREG = a;  // Load the data into the transmit register
}

unsigned char rx()
{
    while(!PIR1bits.RCIF);   // Wait until data is received
    return RCREG;  // Return received character
}

void txstr(unsigned char *s)
{
    while(*s) {
        tx(*s++);
    }
}
int UART_Available() {
    return PIR1bits.RCIF;  // Return 1 if data is available, 0 otherwise
}
