#include "Collisions.h"
#include"Application.h"
#include"Physics.h"
#include "Globals.h"
#include "p2Defs.h"
#include "p2Point.h"

ModuleCollisions::ModuleCollisions(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	LOG("Contructor of Module Physics has been called");
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{
	LOG("Destructor of Module Physics has been called");
}

bool ModuleCollisions::Start()
{
	LOG("Module Collisions succesful Start()");

	return true;
}

void ModuleCollisions::OnCollision(Object& object) {
	
	Object* c1;

	for (int i = 0; i < MAX_OBJECTS && App->physics->world->objects_array[i] != NULL; i++) {
		c1 = App->physics->world->objects_array[i];

		if (&object == c1) continue;

		if (c1->CheckCollisionRect(object)) {
			ForwardPropagation(c1, &object);
		}
	}
}

bool ModuleCollisions::CleanUp() 
{

	LOG("Collisions CleanUp has been called");
	return true;

}

// -----------------------------------------------------

bool Object::CheckCollisionRect(Object& obj)
{


	return !((this->pos.x + this->w < obj.pos.x || obj.pos.x + obj.w < this->pos.x) || (this->pos.y + this->h + PIXEL_TO_METERS(1) < obj.pos.y || obj.pos.y + obj.h + PIXEL_TO_METERS(1) < this->pos.y));


}

void ModuleCollisions::ForwardPropagation(Object* c1, Object* c2) 
{
	//Determines the direction of the collision
	//Calculates distances from the player to the collision
	double collDiference[LAST_COLLISION];
	collDiference[NONE_COLLISION] = NULL;
	collDiference[LEFT_COLLISION] = NULL;
	collDiference[RIGHT_COLLISION] = NULL;
	collDiference[TOP_COLLISION] = NULL;
	collDiference[BOTTOM_COLLISION] = NULL;

	if ((c2->pos.x < c1->pos.x && c2->pos.x + c2->w/2 >= c1->pos.x))
	collDiference[LEFT_COLLISION] = (c2->pos.x + c2->w) - c1->pos.x; //C2 is in the left

	if (c1->pos.x < c2->pos.x && c1->pos.x + c1->w/2 >= c2->pos.x)
	collDiference[RIGHT_COLLISION] = (c1->pos.x + c1->w) - c2->pos.x; //C1 is in the left

	if (c2->pos.y < c1->pos.y && c2->pos.y + c2->h >= c1->pos.y)
	collDiference[TOP_COLLISION] = (c2->pos.y + c2->h) - c1->pos.y; // C2 is on top

	if (c1->pos.y < c2->pos.y && c1->pos.y + c1->h >= c2->pos.y)
	collDiference[BOTTOM_COLLISION] = (c1->pos.y + c1->w) - c2->pos.y; //C1 is on top


	//If a collision from various aixs is detected, it determines what is the closets one to exit from
	dPoint c1pos = { c1->pos.x,c1->pos.y };
	dPoint c2pos = { c2->pos.x,c2->pos.y };

	for (int i = 0; i < LAST_COLLISION; ++i)
	{
		if (collDiference[i] == NULL)
			continue;

		switch (i) {
		case TOP_COLLISION:
			//C1 changes
			c1->pos.y = c2->pos.y + c2->h + PIXEL_TO_METERS(2);
			c1->speed.y *= 1;
			//C2 changes
			c2->pos.y = c1->pos.y - c2->h;
			c2->speed.y *= -1;


			if (c1->pos.y < c2->pos.y && c1->pos.y + c1->h >= c2->pos.y)
				collDiference[BOTTOM_COLLISION] = (c1->pos.y + c1->w) - c2->pos.y; //C1 is on top
			else
				collDiference[BOTTOM_COLLISION] = NULL;
			break;
		case BOTTOM_COLLISION:
			//C1 changes
			c2->pos.y = c1->pos.y + c1->h + PIXEL_TO_METERS(2);
			c2->speed.y *= 1;
			//C2 changes
			c1->pos.y = c2->pos.y - c1->h;
			c1->speed.y *= -1;


			if (c2->pos.y < c1->pos.y && c2->pos.y + c2->h >= c1->pos.y)
				collDiference[TOP_COLLISION] = (c2->pos.y + c2->h) - c1->pos.y; // C2 is on top
			else
				collDiference[TOP_COLLISION] = NULL;

			break;
		case LEFT_COLLISION:
			//C1 changes
			c1->pos.x = c2->pos.x + c2->w;
			//c1->speed.x *= 1;
			//C2 changes
			c2->pos.x = c1->pos.x - c2->w;
			//c2->speed.x *= -1;

			if (c1->pos.x < c2->pos.x && c1->pos.x + c1->w/2 >= c2->pos.x)
				collDiference[RIGHT_COLLISION] = (c1->pos.x + c1->w) - c2->pos.x; //C1 is in the left
			else
				collDiference[RIGHT_COLLISION] = NULL;

			break;
		case RIGHT_COLLISION:
			//C1 changes
			c2->pos.x = c1->pos.x + c1->w;
			//c2->speed.x *= 1;
			//C2 changes
			c1->pos.x = c2->pos.x - c1->w;
			//c1->speed.x *= -1;

			if ((c2->pos.x < c1->pos.x && c2->pos.x + c2->w/2 >= c1->pos.x))
				collDiference[LEFT_COLLISION] = (c2->pos.x + c2->w) - c1->pos.x; //C2 is in the left
			else
				collDiference[LEFT_COLLISION] = NULL;
			break;

		case NONE_COLLISION:
			break;
		}
	}






}
