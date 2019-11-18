#include "Collisions.h"
#include"Application.h"
#include"Physics.h"
#include "Globals.h"

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

	bool checkAllColls = true;

	while (checkAllColls)
	{
		checkAllColls = false;
		for (int i = 0; i < MAX_OBJECTS && App->physics->world->objects_array[i] != NULL; i++)
		{
			

			// avoid checking collisions already checked
			for (int j = 0; j < MAX_OBJECTS && App->physics->world->objects_array[j] != NULL; j++)
			{
				

				if (App->physics->world->objects_array[i]->CheckCollisionRect(*App->physics->world->objects_array[j]) == true)
				{
					checkAllColls = true;
					//Check two times the collision
					if (App->physics->world->objects_array[i]->category = App->physics->world->objects_array[j]->mask)
						//	ForwardPropagation(c1, c2);
						true;
					if (App->physics->world->objects_array[j]->category = App->physics->world->objects_array[i]->mask)
						//	ForwardPropagation(c2, c1);
						true;
				}

			}
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleCollisions::CleanUp() 
{

	LOG("Collisions CleanUp has been called");
	return true;

}

// -----------------------------------------------------

bool Object::CheckCollisionRect(Object& obj)
{
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
}

void ModuleCollisions::ForwardPropagation(Object* object1, Object* object2) {

	if (object1->type == COLL_DYNAMIC) {
		object1->speed.x = ((object1->mass - object2->mass * object2->friction_coefficient) * object1->speed.x + object2->mass * (1 + object1->friction_coefficient) * object2->speed.x) / (object1->mass + object2->mass);
		object1->speed.y = ((object1->mass - object2->mass * object2->friction_coefficient) * object1->speed.y + object2->mass * (1 + object1->friction_coefficient) * object2->speed.y) / (object1->mass + object2->mass);
		object1->pos += object1->speed;
	}
	if (object2->type == COLL_DYNAMIC) {
		object2->speed.x = ((object2->mass - object1->mass * object1->friction_coefficient) * object2->speed.x + object1->mass * (1 + object2->friction_coefficient) * object1->speed.x) / (object1->mass + object2->mass);
		object2->speed.y = ((object2->mass - object1->mass * object1->friction_coefficient) * object2->speed.y + object1->mass * (1 + object2->friction_coefficient) * object1->speed.y) / (object1->mass + object2->mass);
		object2->pos += object2->speed;
	}
}
