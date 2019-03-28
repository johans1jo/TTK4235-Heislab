#include "elevsim.h"

int main() {
    elev_init();
    while(1) {
	elev_set_motor_direction(DIRN_DOWN);
	while(elev_get_floor_sensor_signal() != 0) {}
	elev_set_motor_direction(DIRN_UP);
	while(elev_get_floor_sensor_signal() != 3) {}
    }
}
