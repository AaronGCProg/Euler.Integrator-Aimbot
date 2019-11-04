#include "Globals.h"
#include "Physics.h"

void main() {

	cout << "hello world";

	float xposition = 0;
	float xspeed = 9.8;
	float xground = 50;

	while (xposition != xground) {
		ForwardPropagation(&xposition, &xspeed, &xground);
		printf("%f\n", xposition);
	}
	
	system("pause");

}