#ifndef PHYSICS_H
#define PHYSICS_H

#include "Globals.h"

struct vector{
	float x = 0;
	float y = 0;
};

struct square {
	square(int X, int Y, int W, int H)
	{
		x = X;
		y = Y;
		w = W;
		h = H;
	};

	square() {};

	float x = 0.0f;
	float y = 0.0f;
	float w = 0.0f;
	float h = 0.0f;
};

void ForwardPropagation(vector* position, vector* speed, square* ground);



#endif