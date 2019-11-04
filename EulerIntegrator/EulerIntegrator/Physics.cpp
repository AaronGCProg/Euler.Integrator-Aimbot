#include "Physics.h"

void ForwardPropagation(vector* position, vector* speed, square* ground) {
	vector position_aux;
	position_aux.x = (position->x + speed->x);
	position_aux.y = (position->y + speed->y);
	
	if (position_aux.x < ground->x || position_aux.x > ground->x + ground->w || position_aux.y < ground->y || position_aux.y > ground->y + ground->h) {
		position->x = position_aux.x;		// THIS FUNCTION WILL MOVE THE OBJECT IF NO COLLISION EXISTS
		position->y = position_aux.y;
	}
	
	else if (position_aux.x > ground->x && position->x < ground->x) {
		position->x = ground->x;	// CORRECTS A COLLISION IN THE LEFT SIDE OF THE GROUND
		speed->x *= -1;
	}
	
	else if (position_aux.x < ground->x + ground->w && position->x > ground->x + ground->w) {
		position->x = ground->x + ground->w;	// CORRECTS A COLLISION IN THE RIGHT SIDE OF THE GROUND
		speed->x *= -1;
	}

	else if (position_aux.y > ground->y && position->y < ground->y) {
		position->y = ground->y;	// CORRECTS A COLLISION IN THE UPPER SIDE OF THE GROUND
		speed->y *= -1;
	}

	else if (position_aux.y < ground->y + ground->h && position->y > ground->y + ground->h) {
		position->y = ground->y + ground->h;	// CORRECTS A COLLISION IN THE LOWER SIDE OF THE GROUND
		speed->y *= -1;
	}

}