#include <xc.h>
#define _XTAL_FREQ 20000000     //20M Hz internal crystal for builtin delay

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
    TRISC5 = 0;
    ser_init();
    txstr("Hello world");
    tx('\r');
    txstr("enter your data=");
    while(1)
    {
        unsigned char val;
        if(UART_Available())
            
        {   PORTCbits.RC5 = 1;  // Turn on LED when data is received (temporary indicator)
            tx('\r');
            txstr("Received data=");
            
            val = rx();  // Receive data
            tx(val);     // Echo received data
            tx('\r');
            //txstr("enter your data=");
           
            if (val == '1') {
                PORTCbits.RC5 = 1;  // Turn LED on
                txstr("LED ON\r");
            } else if (val == '0') {
                PORTCbits.RC5 = 0;  // Turn LED off
                txstr("LED OFF\r");
            }
        }
    }
}

void ser_init() {
    TXSTA = 0x20;         // TXEN=1, Asynchronous mode, 8-bit, BRGH=0 (low speed)
    RCSTA = 0b10010000;   // SPEN=1 (Serial port enabled), CREN=1 (Enable reception)
    SPBRG = 17;           // Baud rate set for 9600, assuming 11.0592 MHz clock
}

void tx(unsigned char a)
{
    while(!TXIF);  // Wait until TSR (Transmit Shift Register) is empty
    TXREG = a;  // Load the data into the transmit register
}

unsigned char rx()
{
    while(!RCIF);   // Wait until data is received
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
