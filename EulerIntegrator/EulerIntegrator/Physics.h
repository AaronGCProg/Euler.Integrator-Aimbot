#ifndef PHYSICS_H
#define PHYSICS_H

#include "Globals.h"

struct vector{
	float x = 0;
	float y = 0;
};

struct square {
	float x = 50;
	float y = 50;
	float w = 50;
	float h = 50;
};

void ForwardPropagation(vector* position, vector* speed, square* ground);


#endif