#include "Globals.h"
#include "Physics.h"

int main() {

	vector position;
	vector speed;
	speed.x = 9.8;
	speed.y = 0;
	square ground;
	int timer = 0;

	while (timer != 30) {
		ForwardPropagation(&position, &speed, &ground);
		printf("Position x: %f\nPosition y: %f\n\n", position.x, position.y);
		timer++;
	}

	system("pause");
	return 0;
}