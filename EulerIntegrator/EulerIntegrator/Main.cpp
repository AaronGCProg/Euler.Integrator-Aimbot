#include "Globals.h"
#include "Physics.h"

int main() {



	Object ball;
	ball.x = 0.0;
	ball.speed = 3.0;
	ball.mass = 1.0;


	Integrate2(ball, 0.0);

	/*
	float xposition = 0;
	float xspeed = 9.8;
	float xground = 50;

	while (xposition != xground) {
		ForwardPropagation(&xposition, &xspeed, &xground);
		printf("%f\n", xposition);
	}
	*/
	
	system("pause");
	return 0;
}