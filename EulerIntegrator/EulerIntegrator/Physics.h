
#include "Globals.h"
#include "p2Point.h"

struct Object {

	dPoint pos = { 0,0 };
	dPoint speed={0,0};
	double mass = 0;

	Object(dPoint aPos = { 0,0 }, dPoint aSpeed = {0,0},double aMass=0)
	{
		pos = aPos;
		speed = aSpeed;
		mass = aMass;
	}

};

//float Integrate(Object &object, int time);

void Integrate2(Object &object, dPoint force,double deltaT=(1/60));


