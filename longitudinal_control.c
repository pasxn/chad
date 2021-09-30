#include <xc.h>
#include "longitudinal_control.h"


// Fuzzy logic controller to control the deceleration of chad
unsigned int input_chrisp_max[] = {25, 38 ,50};
float input_fuzzy[] = {0.0, 0.0, 0.0};
unsigned int output_chrisp_max[] = {400, 600 ,800};

int output_speed = 0;


int fuzzy_logic(float front) {
    
    front = (int)front;
    
    // rule table
    if(front>input_chrisp_max[1] && front<input_chrisp_max[2]) {
        input_fuzzy[2] = (front - input_chrisp_max[1])/(input_chrisp_max[2] - input_chrisp_max[1]);
        input_fuzzy[1] = 1 - input_fuzzy[2];
        
    }else if(front>input_chrisp_max[0] && front<input_chrisp_max[1]) {
        input_fuzzy[1] = (front - input_chrisp_max[0])/(input_chrisp_max[1] - input_chrisp_max[0]);
        input_fuzzy[0] = 1 - input_fuzzy[1];
        
    }else if(front<input_chrisp_max[0]) {
        input_fuzzy[0] = 1.0;

    }else if(front>input_chrisp_max[2]) {
        input_fuzzy[2] = 1.0;

    }
    
    // defuzzification
    output_speed = ( (input_fuzzy[0]*output_chrisp_max[0])+(input_fuzzy[1]*output_chrisp_max[1])+(input_fuzzy[2]*output_chrisp_max[2]) )/(input_fuzzy[0]+input_fuzzy[1]+input_fuzzy[2]);
    
    // fixing errors if any
    if(output_speed<1023)
        return (int)output_speed;
    else
        return 1023;
}

// A simple implementation influenced by some control algorithm
float accel = 0;
float error = 0;

float compute_acceleration(float k) {
    if(accel < 1023) {
        error = 1023 - accel;
        accel = accel + error*k;
        return accel;
    }else return 1023.0;
}