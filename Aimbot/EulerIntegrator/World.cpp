#include "World.h"

World::World()
{
	objects_array = new Object*[MAX_OBJECTS];
	memset(objects_array, NULL, MAX_OBJECTS * sizeof(Object*));
	name = "";
	gravity = GRAVITY;
}


World::World(dPoint aGravity, p2SString aName)
{
	objects_array = new Object*[MAX_OBJECTS];

	memset(objects_array, NULL, MAX_OBJECTS * sizeof(Object*));

	gravity = aGravity;
	name = aName;

}


World::~World() {

}


void World::ChangeGravity(double gravX, double gravY) {

	gravity.x = gravX;
	gravity.y = gravY;
}


void World::ChangeGravity(dPoint grav) {

	gravity = grav;
}


void World::AddGravity(double gravX, double gravY) {

	gravity.x += gravX;
	gravity.y += gravY;
}