#include "Trajectory.h"

Trajectory::Trajectory() :
speed(0),
angle(0)
{}


Trajectory::Trajectory(float speed, float angle) : 
speed(speed),
angle(angle)
{}


void Trajectory::operator=(Trajectory aux) {

	speed = aux.speed;
	angle = aux.angle;
}