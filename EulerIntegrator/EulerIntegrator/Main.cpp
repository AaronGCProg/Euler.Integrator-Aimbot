#include "Globals.h"
#include "Physics.h"

int main() {



	Object ball;
	ball.x = 0.0;
	ball.speed = 3.0;
	ball.mass = 1.0;


	Integrate2(ball, 0.0);

	
	system("pause");
	return 0;
}