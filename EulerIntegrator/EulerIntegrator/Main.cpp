#include "Globals.h"
#include "Physics.h"

int main() {

	vector position;
	vector speed;
	speed.x = 9.8;
	speed.y = 9.8;
	square ground;

	ForwardPropagation(&position, &speed, &ground);
	printf("Position x: %f\nPosition y: %f\n\n", position.x, position.y);

	system("pause");
	return 0;
}