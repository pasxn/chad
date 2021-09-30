#include <xc.h>
#include "config.h"
#include "sensors.h"

// variavles to strore duration and distance
unsigned int duration = 0;
float distance = 0;

char flag;

// timer 1 interrupt 
void interrupt timer_1(){
    if(INTCONbits.RBIF){
        INTCONbits.RBIE = 0;         // disable the port change interrupt
        
        if(S_F == 1 || S_R == 1 || S_B == 1 || S_L == 1){
            TMR1L  = 0;
            TMR1H  = 0;       // Clear the timer resistor
            T1CONbits.TMR1ON = 1; // Enable the Timer1
        }

        if(S_F == 0 && flag == 1){
            duration = (TMR1H<<8) | (TMR1L);
            T1CONbits.TMR1ON = 0;   // Disable the timer1
        }
        
        if(S_F == 0 && flag == 2){
            duration = (TMR1H<<8) | (TMR1L);
            T1CONbits.TMR1ON = 0;   // Disable the timer1
        }
        
        if(S_F == 0 && flag == 3){
            duration = (TMR1H<<8) | (TMR1L);
            T1CONbits.TMR1ON = 0;   // Disable the timer1
        }
        
        if(S_F == 0 && flag == 4){
            duration = (TMR1H<<8) | (TMR1L);
            T1CONbits.TMR1ON = 0;   // Disable the timer1
        }
        INTCONbits.RBIF = 0;           // Clear the interrupt flag bit
    }
    INTCONbits.RBIE = 1;               // Enable the port change interrupt
}

// initialization bits for timer 1
void timer_1_init() {
    INTCONbits.GIE = 1;           // Enable the gloabal interrupt
    INTCONbits.RBIE = 1;          // Enable the port change
    T1CONbits.TMR1ON = 0;         // Disable timer1
    T1CONbits.TMR1CS = 0;         // Timer1 internal clock source (Fosc/4)
    T1CONbits.T1CKPS1 = 0;        // 1:2 Presclar value
    T1CONbits.T1CKPS0 = 1;
}

void sensor_init() {
    timer_1_init();
    
    // Trig pins
    TR_F_D = 0; TR_R_D = 0; TR_B_D = 0; TR_L_D = 0;
    // Set Trig pins low state
    TR_F = 0; TR_R = 0; TR_B = 0; TR_L = 0;
    // Echo pins
    S_F_D = 1; S_R_D = 1; S_B_D = 1; S_L_D = 1;
    // Clear Echo pin
    S_F = 0; S_R = 0; S_B = 0; S_L = 0;
}

void sensor_action() {
    // Generate 10us Trig pulse
    TR_F = 1; TR_R = 1; TR_B = 1; TR_L = 1;
    __delay_us(10);
    TR_F = 0; TR_R = 0; TR_B = 0; TR_L = 0;
}

float get_front_distance() {
    flag = 1;
    sensor_action();
    while(S_F == 0);   // Wait for Echo pulse
    distance = ((duration * (0.034)) / 2);
    
    if( distance >=10 && distance <=60 )
        return distance;
    else
        return -1;
}

float get_right_distance() {
    flag = 2;
    sensor_action();
    while(S_R == 0);   // Wait for Echo pulse
    distance = ((duration * (0.034)) / 2);
    
    if( distance >=10 && distance <=60 )
        return distance;
    else
        return -1;
}

float get_back_distance() {
    flag = 3;
    sensor_action();

    while(S_B == 0);   // Wait for Echo pulse
    distance = ((duration * (0.034)) / 2);
    
    if( distance >=10 && distance <=60 )
        return distance;
    else
        return -1;
}

float get_left_distance() {
    flag = 4;
    sensor_action();
    while(S_L == 0);   // Wait for Echo pulse
    distance = ((duration * (0.034)) / 2);
    
    if( distance >=10 && distance <=60 )
        return distance;
    else
        return -1;
}