#define _XTAL_FREQ 20000000 //20 MHz oscillator

// CONFIG
#pragma config FOSC = HS    // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF   // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF  // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF  // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF    // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit 
                            // (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF    // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF    // Flash Program Memory Write Enable bits (Write protection off; 
                            // all program memory may be written to by EECON control)
#pragma config CP = OFF     // Flash Program Memory Code Protection bit (Code protection off)

// Config Pins (direction)
#define PWM_R_D (TRISCbits.TRISC2)
#define PWM_L_D (TRISCbits.TRISC1)

#define M_R_P_D (TRISCbits.TRISC3)
#define M_R_N_D (TRISCbits.TRISC4)
#define M_L_P_D (TRISCbits.TRISC5)
#define M_L_N_D (TRISCbits.TRISC6)

#define TR_F_D (TRISDbits.TRISD0)
#define TR_R_D (TRISDbits.TRISD1)
#define TR_B_D (TRISDbits.TRISD2)
#define TR_L_D (TRISDbits.TRISD3)

#define S_F_D (TRISAbits.TRISA0)
#define S_R_D (TRISAbits.TRISA1)
#define S_B_D (TRISAbits.TRISA2)
#define S_L_D (TRISAbits.TRISA3)


// Config Pins (operation)
#define PWM_R (PORTCbits.RC2) // ccp1
#define PWM_L (PORTCbits.RC1) // ccp2

#define M_R_P (PORTCbits.RC3)
#define M_R_N (PORTCbits.RC4)
#define M_L_P (PORTCbits.RC5)
#define M_L_N (PORTCbits.RC6)

#define TR_F (PORTDbits.RD0)
#define TR_R (PORTDbits.RD1)
#define TR_B (PORTDbits.RD2)
#define TR_L (PORTDbits.RD3)

#define S_F (PORTAbits.RA0)
#define S_R (PORTAbits.RA1)
#define S_B (PORTAbits.RA2)
#define S_L (PORTAbits.RA3)

// Main macros
#define R 1
#define L 0