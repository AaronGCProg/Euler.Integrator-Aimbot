#include "Globals.h"
#include "p2Point.h"

#define MAX_TRACE_POINTS 100

class Trajectory
{
public:
	Trajectory();
	Trajectory(float speed, float angle);
	
	void operator=(Trajectory aux);

public:
	float speed;
	float angle;
	iPoint trace[MAX_TRACE_POINTS];
};

