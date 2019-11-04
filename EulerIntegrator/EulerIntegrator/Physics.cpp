#include "Physics.h"
#include "p2Point.h"


void Integrate2(Object &object, dPoint force,double deltaT) {
	double acc;
	acc = force * (1 / object.mass);
	object.speed += acc * deltaT; //60 fps, one iteration
	object.x += object.speed * deltaT;

	cout<<(object.x);
	cout << "\n"; cout << "\n";
}


/*void ForwardPropagation(float* xposition, float* xspeed, float* xground) {
	float x_aux;
	x_aux = (*xposition + *xspeed);
	if (x_aux < *xground) { *xposition = x_aux; }
	else { *xposition = *xground; }
}*/

