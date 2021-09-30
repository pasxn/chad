#include <xc.h>
#include "config.h"
#include "lateral_control.h"
#include "longitudinal_control.h"
#include "motor_control.h"

// steering the robot
void steer(char toWhichSide) {
    float accel;
    // steering to right
    if(toWhichSide == R) {
        while(accel<1000) {
            accel = compute_acceleration(0.006f);
            setPWMDutyCycle_PWM_L((unsigned int)accel);
        }
    }
    // steering to left
    if(toWhichSide == L) {
        while(accel<1000) {
            accel = compute_acceleration(0.006f);
            setPWMDutyCycle_PWM_R((unsigned int)accel);
        }
    }
}