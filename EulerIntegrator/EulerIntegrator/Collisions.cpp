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
	//FERRAN FILL DE PUTA
	/*
	bool x = false;
	bool y = false;
	if ((this->pos.x < obj.pos.x && this->pos.x + this->w >= obj.pos.x) && ((this->pos.y > obj.pos.y && this->pos.y <= obj.pos.y + obj.h) || (this->pos.y < obj.pos.y && this->pos.y + this->h >= obj.pos.y))) {
		x = true;
		this->current_collision = RIGHT_COLLISION;
		obj.current_collision = LEFT_COLLISION;
	}
	else if ((obj.pos.x < this->pos.x && obj.pos.x + obj.w >= this->pos.x) && ((obj.pos.y > this->pos.y && obj.pos.y <= this->pos.y + this->h) || (obj.pos.y < this->pos.y && obj.pos.y + obj.h >= obj.pos.y))) {
		x = true;
		this->current_collision = LEFT_COLLISION;
		obj.current_collision = RIGHT_COLLISION;
	}
	if ((this->pos.y < obj.pos.y && this->pos.y + this->h >= obj.pos.y) && ((this->pos.x >= obj.pos.x && this->pos.x < obj.pos.x + obj.w) || (this->pos.x + this->w >= obj.pos.x && this->pos.x + this->w < obj.pos.x + obj.w))) {
		y = true;
		this->current_collision = BOTTOM_COLLISION;
		obj.current_collision = TOP_COLLISION;
	}
	else if ((obj.pos.y < this->pos.y && obj.pos.y + obj.h >= this->pos.y) && ((obj.pos.x >= this->pos.x && obj.pos.x < this->pos.x + this->w) || (obj.pos.x + obj.w >= this->pos.x && obj.pos.x + obj.w < this->pos.x + this->w))) {
		y = true;
		this->current_collision = TOP_COLLISION;
		obj.current_collision = BOTTOM_COLLISION;
	}
	if (x || y) {
		return true;
	}
	else { return false; }
	*/
	return !((this->pos.x + this->w < obj.pos.x || obj.pos.x + obj.w < this->pos.x) || (this->pos.y + this->h + 1 < obj.pos.y || obj.pos.y + obj.h + 1 < this->pos.y));


}

void ModuleCollisions::ForwardPropagation(Object* c1, Object* c2) 
{
	//FERRAN FILL DE PUTA
	/*
	if (object1->type == COLL_DYNAMIC) {
		switch (object1->current_collision) {
		case TOP_COLLISION:
			object1->speed.y = -((object1->mass - object2->mass * object2->friction_coefficient) * object1->speed.y + object2->mass * (1 + object1->friction_coefficient) * object2->speed.y) / (object1->mass + object2->mass);
			object1->pos.y += object1->speed.y;
			break;
		case BOTTOM_COLLISION:
			object1->speed.y = ((object1->mass - object2->mass * object2->friction_coefficient) * object1->speed.y + object2->mass * (1 + object1->friction_coefficient) * object2->speed.y) / (object1->mass + object2->mass);
			object1->pos.y += object1->speed.y;
			break;
		case LEFT_COLLISION:
			object1->speed.x = ((object1->mass - object2->mass * object2->friction_coefficient) * object1->speed.x + object2->mass * (1 + object1->friction_coefficient) * object2->speed.x) / (object1->mass + object2->mass);
			object1->pos.x += object1->speed.x;
			break;
		case RIGHT_COLLISION:
			object1->speed.x = -((object1->mass - object2->mass * object2->friction_coefficient) * object1->speed.x + object2->mass * (1 + object1->friction_coefficient) * object2->speed.x) / (object1->mass + object2->mass);
			object1->pos.x += object1->speed.x;
			break;
		}
	}
	if (object2->type == COLL_DYNAMIC) {
		switch (object1->current_collision) {
		case TOP_COLLISION:
			object2->speed.y = -((object2->mass - object1->mass * object1->friction_coefficient) * object2->speed.y + object1->mass * (1 + object2->friction_coefficient) * object1->speed.y) / (object1->mass + object2->mass);
			object2->pos.y += object2->speed.y;
			break;
		case BOTTOM_COLLISION:
			object2->speed.y = ((object2->mass - object1->mass * object1->friction_coefficient) * object2->speed.y + object1->mass * (1 + object2->friction_coefficient) * object1->speed.y) / (object1->mass + object2->mass);
			object2->pos.y += object2->speed.y;
			break;
		case LEFT_COLLISION:
			object2->speed.x = ((object2->mass - object1->mass * object1->friction_coefficient) * object2->speed.x + object1->mass * (1 + object2->friction_coefficient) * object1->speed.x) / (object1->mass + object2->mass);
			object2->pos.x += object2->speed.x;
			break;
		case RIGHT_COLLISION:
			object2->speed.x = -((object2->mass - object1->mass * object1->friction_coefficient) * object2->speed.x + object1->mass * (1 + object2->friction_coefficient) * object1->speed.x) / (object1->mass + object2->mass);
			object2->pos.x += object2->speed.x;
			break;
		}
	}
	*/

	//Determines the direction of the collision
	//Calculates distances from the player to the collision
	int collDiference[LAST_COLLISION];
	collDiference[NONE_COLLISION] = NULL;
	collDiference[LEFT_COLLISION] = NULL;
	collDiference[RIGHT_COLLISION] = NULL;
	collDiference[TOP_COLLISION] = NULL;
	collDiference[BOTTOM_COLLISION] = NULL;

	if ((c2->pos.x < c1->pos.x && c2->pos.x + c2->w >= c1->pos.x))
	collDiference[LEFT_COLLISION] = (c2->pos.x + c2->w) - c1->pos.x; //C2 is in the left

	if (c1->pos.x < c2->pos.x && c1->pos.x + c1->w >= c2->pos.x)
	collDiference[RIGHT_COLLISION] = (c1->pos.x + c1->w) - c2->pos.x; //C1 is in the left

	if (c2->pos.y < c1->pos.y && c2->pos.y + c2->h >= c1->pos.y)
	collDiference[TOP_COLLISION] = (c2->pos.y + c2->h) - c1->pos.y; // C2 is on top

	if (c1->pos.y < c2->pos.y && c1->pos.y + c1->h >= c2->pos.y)
	collDiference[BOTTOM_COLLISION] = (c1->pos.y + c1->w) - c2->pos.y; //C1 is on top


	//If a collision from various aixs is detected, it determines what is the closets one to exit from
	int directionCheck = NONE_COLLISION;
	dPoint c1pos = { c1->pos.x,c1->pos.y };
	dPoint c2pos = { c2->pos.x,c2->pos.y };

	for (int i = 0; i < LAST_COLLISION; ++i)
	{
		if (collDiference[i] == NULL)
			continue;

		switch (i) {
		case TOP_COLLISION:
			//C1 changes
			c1->pos.y = c2pos.y + c2->h + 2;
			c1->speed.y *= 1;
			//C2 changes
			c2->pos.y = c1pos.y - c2->h;
			c2->speed.y *= -1;


			if (c1->pos.y < c2->pos.y && c1->pos.y + c1->h >= c2->pos.y)
				collDiference[BOTTOM_COLLISION] = (c1->pos.y + c1->w) - c2->pos.y; //C1 is on top
			else
				collDiference[BOTTOM_COLLISION] = NULL;
			break;
		case BOTTOM_COLLISION:
			//C1 changes
			c2->pos.y = c1pos.y + c1->h + 2;
			c2->speed.y *= 1;
			//C2 changes
			c1->pos.y = c2pos.y - c1->h;
			c1->speed.y *= -1;


			if (c2->pos.y < c1->pos.y && c2->pos.y + c2->h >= c1->pos.y)
				collDiference[TOP_COLLISION] = (c2->pos.y + c2->h) - c1->pos.y; // C2 is on top
			else
				collDiference[TOP_COLLISION] = NULL;
			break;
		case LEFT_COLLISION:
			//C1 changes
			c1->pos.x = c2pos.x + c2->w;
			c1->speed.x *= 1;
			//C2 changes
			c2->pos.x = c1pos.x - c2->w;
			c2->speed.x *= -1;

			if (c1->pos.x < c2->pos.x && c1->pos.x + c1->w >= c2->pos.x)
				collDiference[RIGHT_COLLISION] = (c1->pos.x + c1->w) - c2->pos.x; //C1 is in the left
			else
				collDiference[RIGHT_COLLISION] = NULL;

			break;
		case RIGHT_COLLISION:
				//C1 changes
				c2->pos.x = c1pos.x + c1->w;
				c2->speed.x *= 1;
				//C2 changes
				c1->pos.x = c2pos.x - c1->w;
				c1->speed.x *= -1;

				if ((c2->pos.x < c1->pos.x && c2->pos.x + c2->w >= c1->pos.x))
					collDiference[LEFT_COLLISION] = (c2->pos.x + c2->w) - c1->pos.x; //C2 is in the left
				else
					collDiference[LEFT_COLLISION] = NULL;
			break;

		case NONE_COLLISION:
			break;
		}
	}






}
