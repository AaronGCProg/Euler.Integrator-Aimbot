#include "Collisions.h"
#include"Application.h"
#include"Physics.h"

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

update_status ModuleCollisions::Update() 
{
	Object* c1;
	Object* c2;

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

bool Object::CheckCollisionRect(const Object& obj) const
{
	return !((this->pos.x /*+ this->rect.w*/ < obj.pos.x || obj.pos.x /*+ r.w*/ < this->pos.x) || (this->pos.y /*+ this->rect.h*/ < obj.pos.y || obj.pos.y /*+ r.h*/ < this->pos.y));
}

void ModuleCollisions::ForwardPropagation(Object* object1, Object* object2) {
	
	// This calculation is done with points. Because there is no volume, this is very ineffective

	// IT WOULD BE RECOMENDABLE TO PUT THE COEFFICIENT OF RESTITUTION AS A VARIABLE UNIQUE TO THE "MATERIAL" OF EACH BODY

	object1->speed.x = ((object1->mass - object2->mass * COEFFICIENT_OF_RESTITUTION) * object1->speed.x + object2->mass * (1 + COEFFICIENT_OF_RESTITUTION) * object2->speed.x) / (object1->mass + object2->mass);
	object1->speed.y = ((object1->mass - object2->mass * COEFFICIENT_OF_RESTITUTION) * object1->speed.y + object2->mass * (1 + COEFFICIENT_OF_RESTITUTION) * object2->speed.y) / (object1->mass + object2->mass);
	object2->speed.x = ((object2->mass - object1->mass * COEFFICIENT_OF_RESTITUTION) * object2->speed.x + object1->mass * (1 + COEFFICIENT_OF_RESTITUTION) * object1->speed.x) / (object1->mass + object2->mass);
	object2->speed.y = ((object2->mass - object1->mass * COEFFICIENT_OF_RESTITUTION) * object2->speed.y + object1->mass * (1 + COEFFICIENT_OF_RESTITUTION) * object1->speed.y) / (object1->mass + object2->mass);

	object1->pos += object1->speed;
	object2->pos += object2->speed;
}
