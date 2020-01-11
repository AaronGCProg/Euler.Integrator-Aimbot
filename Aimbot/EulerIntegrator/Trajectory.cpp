#include "Trajectory.h"

Trajectory::Trajectory() :
speed(0),
angle(0)
{
}


Trajectory::Trajectory(float speed, float angle) : 
speed(speed),
angle(angle)
{
}


void Trajectory::operator=(Trajectory aux) {

	speed = aux.speed;
	angle = aux.angle;

	for(int i = 0;  i < MAX_TRACE_POINTS; i++)
	{
		if (aux.trace[i].x == 0 && aux.trace[i].y == 0)
		{
			return;
		}
		trace[i].x = aux.trace[i].x;
		trace[i].y = aux.trace[i].y;
	}
}