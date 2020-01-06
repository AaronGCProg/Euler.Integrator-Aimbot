#include "Collisions.h"
#include"Application.h"
#include"Physics.h"
#include "Globals.h"
#include "p2Defs.h"
#include "p2Point.h"

ModuleCollisions::ModuleCollisions(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	LOG("Contructor of Module Physics has been called");

	collBewtweenObjectsActive = true;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{
	LOG("Destructor of Module Physics has been called");
}

void ModuleCollisions::OnCollision()
{
	Object* c1;
	Object* c2;

	if (collBewtweenObjectsActive)
		for (int i = 0; i < MAX_OBJECTS; ++i)
		{
			// skip empty colliders
			if (App->physics->world->objects_array[i] == nullptr)
				continue;

			c1 = App->physics->world->objects_array[i];

			// avoid checking collisions already checked
			for (uint k = 0; k < MAX_OBJECTS; ++k)
			{
				// skip empty colliders
				if (App->physics->world->objects_array[k] == nullptr || c1 == App->physics->world->objects_array[k])
					continue;

				c2 = App->physics->world->objects_array[k];

				if (c1->QuickCheckCollision(c2) && c1->AccurateCheckCollision(c2))
				{
					ResolveCollision(c1, c2);
				}
			}
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
		normaldir = { 0,-1 };//default normal

	normaldir.Normalize();

	//Calculate relative velocity
	dPoint rv = c2->speed - c1->speed;
	rv.Normalize();

	// Calculate relative velocity in terms of the normal direction
	double velAlongNormal = rv.Dot(normaldir);//dot product

	// Do not resolve if velocities are separating
	if (velAlongNormal > 0)
	{
		return;
	}
	else
	{
		dPoint p1 = c1->pos + c1->radius;
		dPoint p2 = c2->pos + c2->radius;
		double m_vel1 = c1->speed.Module();
		double m_vel2 = c2->speed.Module();

		dPoint centersdir(p2 - p1);
		centersdir.Normalize();

		c1->pos += (((p2 - p1).Abs().Negate() + (c1->radius + c2->radius)) * 0.5 * centersdir.GetInverse());
		c2->pos += (((p2 - p1).Abs().Negate() + (c1->radius + c2->radius)) * 0.5 * centersdir);

		c1->speed = centersdir.GetInverse() * m_vel1 * c1->friction_coefficient;
		c2->speed = centersdir * m_vel2 * c2->friction_coefficient;
	}
}

void ModuleCollisions::ChangeCollBetweenObj()
{
	collBewtweenObjectsActive = !collBewtweenObjectsActive;
}

void ModuleCollisions::CheckBorderCollision(Object& object)
{
	if ((object.pos.x + object.radius) > PIXEL_TO_METERS(SCREEN_WIDTH) || (object.pos.x - object.radius) < 0)
	{
		object.speed.x = -object.speed.x * object.friction_coefficient;

		if ((object.pos.x + object.radius) > PIXEL_TO_METERS(SCREEN_WIDTH))
			object.pos.x = PIXEL_TO_METERS(SCREEN_WIDTH) - object.radius;

		else if ((object.pos.x - object.radius) < 0)
			object.pos.x = object.radius;

	}

	if ((object.pos.y + object.radius) > PIXEL_TO_METERS(SCREEN_HEIGHT) || (object.pos.y - object.radius) < 0)
	{
		object.speed.y = -object.speed.y * object.friction_coefficient;

		if ((object.pos.y + object.radius) > PIXEL_TO_METERS(SCREEN_HEIGHT))
			object.pos.y = PIXEL_TO_METERS(SCREEN_HEIGHT) - object.radius;

		else if (object.pos.y - object.radius < 0)
			object.pos.y = object.radius;
	}
}