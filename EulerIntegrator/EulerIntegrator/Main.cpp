#include "Globals.h"
#include "Physics.h"

int main() {



	Object ball;

	dPoint force = { 0,0 };
	double deltaT = 1;//one simulation second
	Integrate2(ball,force);

	
	system("pause");
	return 0;
}