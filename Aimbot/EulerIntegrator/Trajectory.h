#include "Globals.h"
#include "p2Point.h"

class Trajectory
{
public:
	Trajectory();
	Trajectory(float speed, float angle);
	
	void operator=(Trajectory aux);

public:
	float speed;
	float angle;
	dPoint trace[100];
};

