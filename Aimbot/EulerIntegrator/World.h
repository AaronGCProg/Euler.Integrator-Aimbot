#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "p2SString.h"
#include "Application.h"
#include "ObjectStruct.h"

struct World
{
	dPoint gravity;

	p2SString name;

	//p2List<Object*>* objects_list;
	//Objects array
	Object** objects_array;
	int index = 0;


	World();

	World(dPoint aGravity, p2SString aName);

	~World();

	void ChangeGravity(double gravX, double gravY);
	void ChangeGravity(dPoint grav);
	void AddGravity(double gravX, double gravY);
};
