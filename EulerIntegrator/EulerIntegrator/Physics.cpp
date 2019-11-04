#include "Physics.h"

void ForwardPropagation(vector* position, vector* speed, square* ground) {
	float x_aux;
	x_aux = (position->x + speed->x);
	if (x_aux < ground->x || x_aux > ground->x + ground->w) { position->x = x_aux; }
	else if (x_aux > ground->x && x_aux < ground->x + ground->w) {
		position->x = ground->x;
		speed->x *= -1;
	}
	else if (x_aux > ground->x && x_aux > ground->x + ground->w) {
		position->x = ground->x + ground->w;
		speed->x *= -1;
	}
}