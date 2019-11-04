#include "Globals.h"
#include "Physics.h"

void main() {

	float xposition = 0;
	float xspeed = 9.8;
	float xground = 50;
	float wground = 50;

	while (xposition != xground) {
		ForwardPropagation(&xposition, &xspeed, &xground, &wground);
		printf("%f\n", xposition);
	}

	system("pause");
}