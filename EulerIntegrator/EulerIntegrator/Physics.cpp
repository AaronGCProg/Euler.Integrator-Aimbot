#include "Physics.h"


void Integrate2(Object &object, dPoint force,double deltaT) {
	dPoint acc;
	acc.x = force.x * (1 / object.mass);
	acc.y = force.y * (1 / object.mass);
	object.speed.x += acc.x * deltaT; //60 fps, one iteration
	object.speed.y += acc.y * deltaT; //60 fps, one iteration
	object.pos.x += object.speed.x * deltaT;
	object.pos.y += object.speed.y * deltaT;

}


/*void ForwardPropagation(float* xposition, float* xspeed, float* xground) {
	float x_aux;
	x_aux = (*xposition + *xspeed);
	if (x_aux < *xground) { *xposition = x_aux; }
	else { *xposition = *xground; }
}*/

