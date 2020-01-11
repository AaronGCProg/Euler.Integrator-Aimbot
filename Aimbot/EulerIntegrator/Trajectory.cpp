#include "Trajectory.h"

Trajectory::Trajectory() :
speed(0),
angle(0)
{
	for (int i = 0; i < 100; i++)
	{
		trace[i] = { -100,-100 };  // -100 is a value used as a flag, no particle can move to that point.
	}
}


Trajectory::Trajectory(float speed, float angle) : 
speed(speed),
angle(angle)
{
	for (int i = 0; i < 100; i++)
	{
		trace[i] = { -100,-100 };  // -100 is a value used as a flag, no particle can move to that point.
	}
}


void Trajectory::operator=(Trajectory aux) {

	speed = aux.speed;
	angle = aux.angle;
	for(int i = 0;  i < 100; i++)
	{
		trace[i].x = aux.trace[i].x;
		trace[i].y = aux.trace[i].y;
	}
}