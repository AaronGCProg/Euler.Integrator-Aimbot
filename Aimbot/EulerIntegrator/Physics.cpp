#include "Physics.h"
#include "Render.h"
#include "Application.h"
#include "Collisions.h"

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	LOG("Contructor of Module Physics has been called");
}

// Destructor
ModulePhysics::~ModulePhysics()
{
	LOG("Destructor of Module Physics has been called");
}

update_status ModulePhysics::Update(float dt) {

	//Here goes a call of Integrate() to all objects of the world
	for (int i = 0; i < MAX_OBJECTS && world->objects_array[i] != NULL; i++)
	{
		Integrate(*world->objects_array[i], world->gravity, dt);
	}
	return UPDATE_CONTINUE;

}

update_status ModulePhysics::PostUpdate()
{
	//Paint all objects of the world to the screen

	for (int i = 0; i < MAX_OBJECTS && world->objects_array[i] != nullptr; i++)
	{
		SDL_Rect rect;
		rect.x = METERS_TO_PIXELS(world->objects_array[i]->pos.x);
		rect.y = METERS_TO_PIXELS(world->objects_array[i]->pos.y);
		rect.w = METERS_TO_PIXELS(world->objects_array[i]->w);
		rect.h = METERS_TO_PIXELS(world->objects_array[i]->h);

		switch(world->objects_array[i]->type)
		{ 
		case COLL_DYNAMIC:
			//Borderless RED
			App->renderer->DrawQuad(rect, 255, 0, 0, 255, false, true);
			break;
		case COLL_STATIC:
			//Borderless LIGHT BLUE
			App->renderer->DrawQuad(rect, 0, 255, 255, 255, false, true);
			break;
		
		}
	}

	return UPDATE_CONTINUE;

}


bool ModulePhysics::Start() {
	LOG("Module Physics succesful Start()");
	//Create world
	world = new World();

	return true;
}

bool ModulePhysics::CleanUp() {

	//Destroy world
	//Clear all pointers
	//Clear all arrays
	for (int i = 0; i < MAX_OBJECTS && world->objects_array[i] != NULL; i++)
	{
		delete world->objects_array[i];
		world->objects_array[i] = nullptr;
	}

	delete world;
	world = nullptr;

	LOG("Physics CleanUp has been called");
	return true;

}


void ModulePhysics::Integrate(Object& object, dPoint gravity, float dt)
{
	dPoint acc = { 0,0 };

	if (object.mass >= 0.001) { //if the mass of the object is zero, forces and gravity have no affect in it so we do not calculate them

		dPoint aerodinamic_drag;
		aerodinamic_drag.x = object.CalculateAerodinamicCoeficientX();
		aerodinamic_drag.y = object.CalculateAerodinamicCoeficientY();
		object.AddForce(aerodinamic_drag);
		acc.x = (object.force.x * (1 / object.mass)) * dt;
		acc.y = (object.force.y * (1 / object.mass)) * dt;
		acc.x += gravity.x * dt;
		acc.y += gravity.y * dt;



	}
	object.force = { 0,0 }; //we reset all the forces of the object after converting them to acceleration, to start a new frame without forces

	object.speed.x += acc.x * dt;
	object.speed.y += acc.y * dt; //60 fps, one iteration

	object.pos.x += object.speed.x * dt;
	object.pos.y += object.speed.y * dt;

	App->collisions->OnCollision(object);
}

void ModulePhysics::AddObject(Object& obj)
{
	int i = world->index % MAX_OBJECTS; //search position in array. If full, start from the beggining

	if (world->objects_array[i] != nullptr)
	{
		if ( world->objects_array[i]->type != COLL_STATIC)
		{
		delete world->objects_array[i]; //if there is something, delete it
		world->objects_array[i] = nullptr; //clear the pointer
		}
	}
	world->objects_array[i] = &obj; //ad the object

	world->index++;
}

bool ModulePhysics::DeleteObject(Object& obj)
{
	bool ret = false;
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		if (obj == *world->objects_array[i])
		{
			delete world->objects_array[i]; //if there is something, delete it
			world->objects_array[i] = nullptr; //clear the pointer
			ret = true;
		}

	}
	return ret;
}

int ModulePhysics::FindObject(Object& obj) {

	int ret = -1;

	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		if (obj == *world->objects_array[i])
		{
			ret = i;
		}

	}
	return ret;
}

int ModulePhysics::IsInsideObject(dPoint& position) {	// Checks if the point is inside the object (check .h for further info)
	position.x = PIXEL_TO_METERS(position.x);
	position.y = PIXEL_TO_METERS(position.y);
	for (int i = 0; i < MAX_OBJECTS; i++) {
		if (world->objects_array[i] != nullptr) {
			if (position.x >= world->objects_array[i]->pos.x && position.x <= world->objects_array[i]->pos.x + world->objects_array[i]->w &&
				position.y >= world->objects_array[i]->pos.y && position.y <= world->objects_array[i]->pos.y + world->objects_array[i]->h) {
				return i;
			}
		}
	}
	return -1;
}