
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

#include "robot.hh"

using std::cout;
using std::endl;

int Scheme = 0;
int Row = 1;
int FullSweep = 0;

void
callback(Robot* robot)
{
	if (Scheme == 0) {
		if (robot->range < 0.6) {
			robot->set_vel(-0.7,0.7);
			Scheme = 1;
			cout << "Scheme 1" << endl;
		} else {
			robot->set_vel(2.0,2.0);
		}
	} else if (Scheme == 1) {
		if (fmod((robot->pos_t + 6.28),6.28) > 1.56) {
			robot->set_vel(2.0,2.0);
			Scheme = 2;
			cout << "Scheme 2" << endl;
		}
	} else if (Scheme == 2) {
		if (robot->range > 100) {
			FullSweep = 0;
			Scheme = 3;
			cout << "Scheme 3" << endl;
		} else if (FullSweep = 1 && robot->range < 0.6) {
			robot->set_vel(0.7,-0.7);
			Scheme = 6;
			cout << "Scheme 6" << endl;
		} else if (robot->range < 0.6) {
			robot->set_vel(-0.7,0.7);
			Scheme = 4;
			cout << "Scheme 4" << endl;
		}
	} else if (Scheme == 3) {
		if (robot->range < 100) {
			robot->set_vel(0.7,-0.7);
			Scheme = 5;
			cout << "Scheme 5" << endl;
		}
	} else if (Scheme == 4) {
		if (fmod((robot->pos_t + 6.28),6.28) > 4.68) {
			FullSweep = 1;
			robot->set_vel(2.0,2.0);
			Scheme = 2;
			cout << "Scheme 2" << endl;
		}
	} else if (Scheme == 5) {
		if (fmod((robot->pos_t + 6.28),6.28) < 0.1) {
			Scheme = 0;
			cout << "Scheme 0" << endl;
		}
	} else if (Scheme == 6) {
		do{
		} while(fmod((robot->pos_t + 6.28),6.28) > 3.14);
		do{
			robot->set_vel(2.0,2.0);
		} while(robot->range > 0.2);
		do{
			robot->set_vel(0.7,-0.7);
		} while(fmod((robot->pos_t + 6.28),6.28) > 1.6);
		do{
			robot->set_vel(2.0,2.0);
		} while(robot->range < 100);
		do{
			robot->set_vel(2.0,2.0);
		} while(robot->range > 100);
		do{
			robot->set_vel(-0.7,0.7);
		} while(fmod((robot->pos_t + 6.28),6.28) > 3.14);
		robot->set_vel(2.0,2.0);
		sleep(5);
		do{
			robot->set_vel(0.7,-0.7);
		} while(fmod((robot->pos_t + 6.28),6.28) > 1.6);
		robot->set_vel(2.0,2.0);
	}
}

int
main(int argc, char* argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    return 0;
}
