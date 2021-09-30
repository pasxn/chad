#ifndef __MOTOR_CONTROL__
#define __MOTOR_CONTROL__

void timer_two_setup(unsigned char period);
void PWMinit(unsigned char timer_input);
void setPWMDutyCycle_PWM_L(unsigned int duty);
void setPWMDutyCycle_PWM_R(unsigned int duty);
void motor_init(char pr2);
void move_foward();
void turn(char toWhichSide, float front);
void stop(float front);

#endif