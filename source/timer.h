/**
 * @file
 * @brief A simple module to controll the timer of the door.
 */ 
#include <stdio.h>
#include <time.h>

//spør om dette er en global variabel - i såfall må den kommenteres
clock_t before;

/**
 * @brief Sets the starttime to the current time.
 */
void timer_start_timer(void);

/**
 * @brief Checks if it's three seconds since the starttime. 
 *  
 * @return 1 if true, 0 if not.
 */
int timer_time_out(void);
