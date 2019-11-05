#include "Physics.h"


ModuleIntegrator::ModuleIntegrator()
{
}


ModuleIntegrator::~ModuleIntegrator()
{
}


void ModuleIntegrator::Integrate(Object& object, dPoint gravity)
{
	dPoint acc;

	acc.x = object.force.x * (1 / object.mass);
	acc.y = object.force.y * (1 / object.mass);

	object.speed.x += acc.x;
	object.speed.y += acc.y; //60 fps, one iteration

	object.pos.x += object.speed.x;
	object.pos.y += object.speed.y;
}



/*void ForwardPropagation(float* xposition, float* xspeed, float* xground) {
	float x_aux;
	x_aux = (*xposition + *xspeed);
	if (x_aux < *xground) { *xposition = x_aux; }
	else { *xposition = *xground; }
}*/

