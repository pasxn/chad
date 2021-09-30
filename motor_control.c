#include <xc.h>
#include "config.h"
#include "motor_control.h"
#include "longitudinal_control.h"
#include "lateral_control.h"

void timer_two_setup(unsigned char period) {
    PR2 = period;                 // configure the timer2 period
    T2CONbits.TMR2ON = 1;       // timer two ON
    T2CONbits.T2CKPS1 = 0;
    T2CONbits.T2CKPS1 = 0;      // setting up pre scaler value as 1
}

void PWMinit(unsigned char timer_input) {
    CCP1CON = 0x0c;             // Configure CCP1 module in PWM mode
    CCP2CON = 0x0c;             // Configure CCP1 module in PWM mode
    timer_two_setup(timer_input);
}

void setPWMDutyCycle_PWM_R(unsigned int duty) {   // Give a value in between 0 and 1023 for duty cycle
    CCP1CONbits.CCP1M = 0b1111;             //  PWM mode
    CCPR1L = duty>>2;                       // storing the 8 MSBs
    CCP1CON = CCP1CON & 0xcf;               // making 4th and 5th bit 0
    CCP1CON = CCP1CON | (0x30&(duty<<4));
}

void setPWMDutyCycle_PWM_L(unsigned int duty) {   // Give a value in between 0 and 1023 for duty cycle
    CCP2CONbits.CCP2M = 0b1111;           //  PWM mode
    CCPR2L = duty>>2;                       // storing the 8 MSBs
    CCP2CON = CCP2CON & 0xcf;               // making 4th and 5th bit 0
    CCP2CON = CCP2CON | (0x30&(duty<<4));
}

void motor_init(char pr2) {                
    PWM_R_D = 0; PWM_L_D = 0;   // make CCP1, CCP2 pins as output for the PWM signal
    
    M_R_P_D = 0; M_R_N_D = 0; M_L_P_D = 0; M_L_N_D = 0;
    
    M_R_P = 0; M_R_N = 0; M_L_N = 0; M_L_P = 0;
    
    PWMinit(pr2);              // initializing the PWM
}

// moving the robot forward 
void move_foward() {
    M_R_P = 1; M_R_N = 0; M_L_P = 1; M_L_N = 0;
    float accel;
    while(accel<1000) { // accelerate until duty cycle is 1000 
        accel = compute_acceleration(0.006f);
        setPWMDutyCycle_PWM_R((unsigned int)accel);
        setPWMDutyCycle_PWM_L((unsigned int)accel);
    }
}

// calling the steering function 
void turn(char toWhichSide, float front) {
    setPWMDutyCycle_PWM_R(fuzzy_logic(front));
    setPWMDutyCycle_PWM_L(fuzzy_logic(front));

    steer(toWhichSide);
}

// stopping the robot
void stop(float front) {
    setPWMDutyCycle_PWM_R(fuzzy_logic(front));
    setPWMDutyCycle_PWM_L(fuzzy_logic(front));

    M_R_P = 0; M_R_N = 0; M_L_N = 0; M_L_P = 0;
}