//
//  timer.h
//  
//
//  Created by Siri Hegsvold on 24/03/2019.
//

#ifndef timer_h
#define timer_h

#include <stdio.h>
#include <time.h>

#endif /* timer_h */

int msec = 0, trigger = 300;  /* tre sekunder */
clock_t before;

void start_timer();

int time_out();
