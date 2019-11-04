#include "Physics.h"

void ForwardPropagation(vector* position, vector* speed, square* ground) {
	vector aux;
	aux.x = (position->x + speed->x);
	aux.x = (position->y + speed->y);
	
	if (aux.x < ground->x || aux.x > ground->x + ground->w || aux.y < ground->y || aux.y > ground->y + ground->h) {
		position->x = aux.x;		// THIS FUNCTION WILL MOVE THE OBJECT IF NO COLLISION EXISTS
		position->y = aux.y;
	}
	
	else if (aux.x > ground->x && aux.x < ground->x + ground->w) {
		position->x = ground->x;	// CORRECTS A COLLISION IN THE LEFT SIDE OF THE GROUND
		speed->x *= -1;
	}
	
	else if (aux.x > ground->x && aux.x > ground->x + ground->w) {
		position->x = ground->x + ground->w;	// CORRECTS A COLLISION IN THE RIGHT SIDE OF THE GROUND
		speed->x *= -1;
	}
}