#include "Collisions.h"
#include"Application.h"
#include"Physics.h"
#include "Globals.h"
#include "p2Defs.h"
#include "p2Point.h"

ModuleCollisions::ModuleCollisions(Application* app, bool start_enabled) : Module(app, start_enabled) {
	LOG("Contructor of Module Physics has been called");
}

// Destructor
ModuleCollisions::~ModuleCollisions() {
	LOG("Destructor of Module Physics has been called");
}

void ModuleCollisions::OnCollision(Object& object) 
{
	if (object.pos.x > PIXEL_TO_METERS(SCREEN_WIDTH)  || object.pos.x < 0)
	{
		object.speed.x = -object.speed.x * object.friction_coefficient;

		if (object.pos.x > PIXEL_TO_METERS(SCREEN_WIDTH))
			object.pos.x = PIXEL_TO_METERS(SCREEN_WIDTH);

		else if(object.pos.x < 0)
			object.pos.x = 0;

	}

	if (object.pos.y > PIXEL_TO_METERS(SCREEN_HEIGHT) || object.pos.y < 0)
	{
		object.speed.y = -object.speed.y * object.friction_coefficient;

		if (object.pos.y > PIXEL_TO_METERS(SCREEN_HEIGHT))
			object.pos.y = PIXEL_TO_METERS(SCREEN_HEIGHT);

		else if (object.pos.y < 0)
			object.pos.y = 0;
	}


}

bool ModuleCollisions::CleanUp()
{

	LOG("Collisions CleanUp has been called");
	return true;

}