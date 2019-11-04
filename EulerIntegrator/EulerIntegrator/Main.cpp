#include "Globals.h"
#include "Physics.h"

int main() 
{
	p2List<square*> list;

	vector position;
	vector speed;
	speed.x = 9.8;
	speed.y = 0;
	square* ground = new square( 50,0,50,50 );
	list.add(ground);
	delete ground;

	square* ground1 = new square(50, 0, 50, 50);
	list.add(ground1);
	delete ground1;


	int timer = 0;


	while (timer != 30) {
		for (p2List_item<square*>* iterator = list.start; iterator != NULL; iterator = iterator->next)
		{
			ForwardPropagation(&position, &speed, iterator->data);
			printf("Position x: %f\nPosition y: %f\n\n", position.x, position.y);

		}
		timer++;
	}

	system("pause");
	return 0;
}