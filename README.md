# HW05
Youtube Video: https://youtu.be/wOTZB8sdw_U

Note: Hello There
I am Matthew Pashkowsky
This is my submission for HW 5 for CS5335
OBS needs driver updates and I do not know how to do that
SimpleScreenRecorder is the only recorder I could get to record my screen, but it doesn’t record my audio



My idea was to initially stick to the left. The robot would go left as far as possible in the first row, before heading right along the front wall to find the first door and go through it. The robot would go straight until it hit a wall, at which point it would try to turn left to try to find a door. If it hit a side wall, it would turn around, go through the first door, and let the cycle continue. It was keeping track of the rows as well, so once it hit row 11 it would find the goal.

I realized the issue with this approach was that when going left, it could still hit the rightmost door, breaking the assumption that it was always going through the leftmost available door, invalidating the program. So I tried implementing wall follow with the program keeping track of row by the number of left turns it had to do. However, I was never able to make these left turns, as trying to turn once the robot no longer saw any walls led to turning too soon and crashing into a wall, and I had no timer to delay the turn a second or two.

Thus, I tried the strategy shown in the video. It goes straight until it hits a wall, turns left to find a door if it doesn’t find it turns around to find the first door of the right, and keeps heading to the door. However, as shown in the video, the sensor refused to acknowledge when it hit a wall after turning left and glitched out

At that point in video, nothing was setting the velocity to go straight, and that was a bug in the robot itself

Code:

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
