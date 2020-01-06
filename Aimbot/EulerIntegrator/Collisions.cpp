#include "Collisions.h"
#include"Application.h"
#include"Physics.h"
#include "Globals.h"
#include "p2Defs.h"
#include "p2Point.h"

ModuleCollisions::ModuleCollisions(Application* app, bool start_enabled) : Module(app, start_enabled) {
	LOG("Contructor of Module Physics has been called");

	collBewtweenObjectsActive = true;
}

// Destructor
ModuleCollisions::~ModuleCollisions() {
	LOG("Destructor of Module Physics has been called");
}

void ModuleCollisions::OnCollision(Object& object) 
{
	Object* c1;

	if(collBewtweenObjectsActive)
	for (int i = 0; i < MAX_OBJECTS && App->physics->world->objects_array[i] != NULL; i++) {
		c1 = App->physics->world->objects_array[i];

		if (&object == c1) continue;

		if (c1->CheckCollision(object))
		{
			ResolveCollision(c1, &object);
		}
	}

	if ((object.pos.x + object.radius) > PIXEL_TO_METERS(SCREEN_WIDTH)  || (object.pos.x - object.radius) < 0)
	{
		object.speed.x = -object.speed.x * object.friction_coefficient;

		if ((object.pos.x + object.radius) > PIXEL_TO_METERS(SCREEN_WIDTH))
			object.pos.x = PIXEL_TO_METERS(SCREEN_WIDTH) - object.radius;

		else if((object.pos.x - object.radius) < 0)
			object.pos.x = object.radius;

	}

	if ( (object.pos.y + object.radius) > PIXEL_TO_METERS(SCREEN_HEIGHT) || (object.pos.y-object.radius) < 0)
	{
		object.speed.y = -object.speed.y * object.friction_coefficient;

		if ((object.pos.y + object.radius) > PIXEL_TO_METERS(SCREEN_HEIGHT))
			object.pos.y = PIXEL_TO_METERS(SCREEN_HEIGHT) - object.radius;

		else if (object.pos.y - object.radius < 0)
			object.pos.y = object.radius;
	}
}

bool ModuleCollisions::CleanUp()
{
	LOG("Collisions CleanUp has been called");
	return true;
}

void ModuleCollisions::ResolveCollision(Object* c1, Object* c2)
{
	//Calculates the normal dir
	double modul;
	dPoint normaldir = c2->speed + c1->speed;
	
	if (normaldir.x <= 0.001f && normaldir.y <= 0.001f)
		normaldir = { 0,-1 };

	normaldir.Normalize();

	//Calculate relative velocity
	dPoint rv = c2->speed - c1->speed;

	// Calculate relative velocity in terms of the normal direction
	double velAlongNormal = rv.Dot(normaldir);//dot product

	// Do not resolve if velocities are separating
	if (velAlongNormal > 0)
		return;
	else
	{
		dPoint p1 = c1->pos + c1->radius;
		dPoint p2 = c2->pos + c2->radius;

		dPoint centersdir= p2 - p1;

		centersdir.Normalize();
		centersdir *= 10;

		c1->speed = centersdir.GetInverse();
		c2->speed = centersdir;
	}

}

int ModuleCollisions::CheckCollisionDir(Object* c1, Object* c2)
{
	//Determines the direction of the collision
	//Calculates distances from the player to the collision
	int collDiference[DIRECTION_MAX];
	collDiference[DIRECTION_LEFT] = (c1->pos.x + c2->radius*2) - c1->pos.x;
	collDiference[DIRECTION_RIGHT] = (c1->pos.x + c1->radius*2) - c2->pos.x;
	collDiference[DIRECTION_UP] = (c2->pos.y + c2->radius*2) - c1->pos.y;
	collDiference[DIRECTION_DOWN] = (c1->pos.y + c1->radius*2) - c2->pos.y;


	//If a collision from various aixs is detected, it determines what is the closets one to exit from
	int directionCheck = DIRECTION_NONE;

	for (int i = 0; i < DIRECTION_MAX; ++i)
	{
		if (directionCheck == DIRECTION_NONE)
			directionCheck = i;
		else if ((collDiference[i] < collDiference[directionCheck]))
			directionCheck = i;
	}

	return directionCheck;
}

void ModuleCollisions::ChangeCollBetweenObj()
{
	collBewtweenObjectsActive = !collBewtweenObjectsActive;
}