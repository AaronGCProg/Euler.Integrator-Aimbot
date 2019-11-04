
#include "Globals.h"

struct Object {

	double x;
	double speed;
	//float acceleration;
	double mass;

};

//float Integrate(Object &object, int time);

void Integrate2(Object &object, double force);

/*#ifndef PHYSICS_H
#define PHYSICS_H

#include "Globals.h"

void ForwardPropagation(float* xposition, float* xspeed, float* xground);

#endif*/

