#include "Globals.h"
#include "Physics.h"

int main() {



	Object ball;
	ball.SetMass(1);
	ball.SetPos({0,2});
	ball.SetSpeed({ 0,2 });


	dPoint force = { 0,2 };
	double deltaT = 1;//one simulation second
	Integrate2(ball,force,deltaT);

	
	system("pause");
	return 0;
}