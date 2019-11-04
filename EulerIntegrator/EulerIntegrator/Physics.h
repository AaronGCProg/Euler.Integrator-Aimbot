#include "Globals.h"

struct Object {

	double x;
	double speed;
	//float acceleration;
	double mass;

};

//float Integrate(Object &object, int time);

void Integrate2(Object &object, double force);