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


void ModuleCollisions::ForwardPropagation(Object* c1, Object* c2)
{
	double mass1=c1->mass;
	double mass2=c2->mass;
	if (mass1 <= 0.01) mass1 = 100000000;
	if (mass2 <= 0.01) mass2 = 100000000;


	//Calculates the normal dir
	double modul;
	dPoint normaldir = c2->speed + c1->speed;
	if (normaldir.x <=0.001f&&normaldir.y<=0.001f)
		normaldir = { 0,-1 };

	modul = sqrt((normaldir.x * normaldir.x) + (normaldir.y * normaldir.y));
	normaldir.x = (normaldir.x / modul);
	normaldir.y = (normaldir.y / modul);

	//Calculate relative velocity
	dPoint rv = c2->speed - c1->speed;
	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = (rv.x * normaldir.x) + (rv.y * normaldir.y);//dot product

	// Do not resolve if velocities are separating
	if (velAlongNormal > 0)
		return;

	// Calculate restitution
	//float e = min(A.restitution, B.restitution); //if we had restitution for each material this would have to happen
	// Calculate impulse scalar
	float j = -(1 + RESTITUTION_COEFICIENT) * velAlongNormal;
	j /= 1 / mass1 + 1 / mass2;
	// Apply impulse
	dPoint impulse;
	impulse.x = j * normaldir.x;
	impulse.y = j * normaldir.y;

	c1->speed.x -= 1 / mass1 * impulse.x;
	c1->speed.y -= 1 / mass1 * impulse.y;

	c2->speed.x += 1 / mass2 * impulse.x;
	c2->speed.y += 1 / mass2 * impulse.y;



	//dPoint c1center;
	//c1center.x = c1->pos.x + (c1->w * 0.5);
	//c1center.y = c1->pos.y + (c1->h * 0.5);
	//dPoint c2center;
	//c2center.x = c2->pos.x + (c2->w * 0.5);
	//c2center.y = c2->pos.y + (c2->h * 0.5);

	//c1->speed = { 0,0 };
	//c2->speed = { 0,0 };
	////Determines the direction of the collision
	////Calculates distances from the player to the collision
	//double modul;
	//dPoint direction = c1center - c2center;
	//dPoint inverted_dir;

	//modul = sqrtf((direction.x * direction.x) + (direction.y * direction.y));

	//double forcescalar;//scalar that multiplies the foce direction, it will change with the proximity of the centers

	//forcescalar = (1 / (modul+1)); //the force scalar has to range between 1 and 0.42
	//forcescalar -= (1 / (sqrtf(2) + 1));//max case
	////forcescalar *= sqrtf(2);
	//forcescalar += 1;
	//forcescalar *= forcescalar*20000;


	//direction.x = (direction.x / modul)*forcescalar;
	//direction.y = (direction.y / modul)* forcescalar;


	//inverted_dir.x = direction.x*-1;
	//inverted_dir.y = direction.y * -1;

	//c1->AddForce(direction);
	//c2->AddForce(inverted_dir);


	//tried conservation of energy, doesn't work
//	dPoint vfc1;
//	vfc1.x= (c1->speed.x * (c1->mass - c2->mass)) + (2 *c2->speed.x*c2->speed.x*c2->mass) /(c1->mass+c2->mass);
//	vfc1.y = (c1->speed.y * (c1->mass - c2->mass)) + (2 * c2->speed.y * c2->speed.y * c2->mass) / (c1->mass + c2->mass);
//	dPoint vfc2;
//	vfc2.x = (c2->speed.x * (c2->mass - c1->mass)) + (2 * c1->speed.x * c1->speed.x * c1->mass) / (c2->mass + c1->mass);
//	vfc2.y = (c2->speed.y * (c2->mass - c1->mass)) + (2 * c1->speed.y * c1->speed.x * c1->mass) / (c2->mass + c1->mass);
//	c1->AddForce(vfc2);
//	c2->AddForce(vfc1);
}







