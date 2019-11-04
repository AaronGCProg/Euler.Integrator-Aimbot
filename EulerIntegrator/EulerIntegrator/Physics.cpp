#include "Physics.h"

void ForwardPropagation(float* xposition, float* xspeed, float* xground, float* wground) {
	float x_aux;
	x_aux = (*xposition + *xspeed);
	if (x_aux < *xground || x_aux > * xground + *wground) { *xposition = x_aux; }
	else if (x_aux > * xground && x_aux < *xground + *wground) {
		*xposition = *xground;
		*xspeed *= -1;
	}
	else if (x_aux > * xground && x_aux > * xground + *wground) {
		*xposition = *xground + *wground;
		*xspeed *= -1;
	}
}