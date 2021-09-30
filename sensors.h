#ifndef __TIMER__
#define __TIMER__

void interrupt timer_1();
void timer_1_init();
void sensor_action();
void sensor_init();

float get_front_distance();
float get_right_distance();
float get_back_distance();
float get_left_distance();

#endif