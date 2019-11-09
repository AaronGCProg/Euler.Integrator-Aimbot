#include "Collisions.h"
#include "Physics.h"

ModuleCollisions::ModuleCollisions(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	LOG("Contructor of Module Physics has been called");
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{
	LOG("Destructor of Module Physics has been called");
}

update_status ModuleCollisions::Update() {

	return UPDATE_CONTINUE;

}

bool ModuleCollisions::Start() {
	LOG("Module Collisions succesful Start()");

	return true;
}

bool ModuleCollisions::CleanUp() {

	LOG("Collisions CleanUp has been called");
	return true;

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
