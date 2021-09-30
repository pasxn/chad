#include <xc.h>
#include "config.h"
#include "sensors.h"
#include "motor_control.h"
#include "longitudinal_control.h"
#include "lateral_control.h"

void main(void) {
    // initializing sensors and motors
    sensor_init();
    motor_init(0xff);
    
    // variables to store the sensor outputs
    float front;
    float right;
    float back;
    float left;
    
    int prev_left = 0;
    int prev_right = 0;
    
    while(1) {
        
        // checking the sensors once per each frame (each while loop iteration)
        front = get_front_distance();
        right = get_right_distance();
        back = get_back_distance();
        left = get_left_distance();
        
        
        if( (front == -1) && (right == -1) && (left == -1) ) {
            // when the robot has never observed a wall
            if(prev_right == 0 && prev_left == 0) {
                move_foward();
                
                prev_left = 0;
                prev_right = 0;
            }
            
            // when the robot has arrived at an exterior 90 degree turn 
            if(prev_right == 1){
                turn(R, front);
                
                prev_left = 0;
                prev_right = 0; 
            }
            
            // when the robot has arrived at an exterior 90 degree turn 
            if(prev_left == 1){
                turn(L, front);
                
                prev_left = 0;
                prev_right = 0;
            }
        }
        
        // following the wall 
        if(left >= 15 && left <= 20) {
            prev_left = 1;
            move_foward();
        }
        // following the wall 
        if(right >= 15 && right <= 20) {
            prev_right = 1;
            move_foward(); 
        }
        
        // when the robot detects a wall in front
        if(front <= 60) {
            prev_left = 0;
            prev_right = 0;
            
            // artificial stop 
            if( (left >= 10 && left <= 20) && (right >= 10 && right <= 20) ){
                stop(front);
            } 
            
            // interior 90 degree turn
            if(left >= 15 && left <= 20) {
                turn(R, front);
            }
            
            // interior 90 degree turn
            if(left >= 15 && left <= 20) {
                turn(L, front);
            }
        }      
    }
}