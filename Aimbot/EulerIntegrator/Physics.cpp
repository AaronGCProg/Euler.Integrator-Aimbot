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

update_status ModulePhysics::Update(float dt)
{
	//Here goes a call of Integrate() to all objects of the world
	for (int i = 0; i < MAX_OBJECTS && world->objects_array[i] != NULL; i++)
	{
		if (world->objects_array[i] == nullptr) continue;
		Integrate(world->objects_array[i], world->gravity, dt);
	}
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate() {
	//Paint all objects of the world to the screen

	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		if (world->objects_array[i] != nullptr) {
			App->renderer->DrawCircle(METERS_TO_PIXELS(world->objects_array[i]->pos.x), METERS_TO_PIXELS(world->objects_array[i]->pos.y), METERS_TO_PIXELS(world->objects_array[i]->radius), 255, 255, 255, 255, false);
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
	for (int i = 0; i < MAX_OBJECTS && world->objects_array[i] != NULL; i++) {
		delete world->objects_array[i];
		world->objects_array[i] = nullptr;
	}

	delete world;
	world = nullptr;

	LOG("Physics CleanUp has been called");
	return true;

}


void ModulePhysics::Integrate(Object* object, dPoint gravity, float dt)
{
	if (object->noPhys)
	{
		App->collisions->CheckBorderCollision(object);
		return;
	}

	dPoint acc = { 0,0 };

	//if the mass of the object is zero, forces and gravity have no affect in it so we do not calculate them
	if (object->mass >= 0.001) 
	{ 
		dPoint aerodinamic_drag;
		aerodinamic_drag.x = object->CalculateAerodinamicCoeficientX();
		aerodinamic_drag.y = object->CalculateAerodinamicCoeficientY();
		object->AddForce(aerodinamic_drag);
		acc.x = (object->force.x * (1 / object->mass)) * dt;
		acc.y = (object->force.y * (1 / object->mass)) * dt;
		acc.x += gravity.x * dt;
		acc.y += gravity.y * dt;
	}

	object->force = { 0,0 }; //we reset all the forces of the object after converting them to acceleration, to start a new frame without forces

	object->speed.x += acc.x * dt;
	object->speed.y += acc.y * dt; //60 fps, one iteration

	object->pos.x += object->speed.x * dt;
	object->pos.y += object->speed.y * dt;

	App->collisions->CheckBorderCollision(object);
	App->collisions->OnCollision(object);
}

void ModulePhysics::AddObject(Object* obj) {

	for (int i = 0; i < MAX_OBJECTS; i++) {
		if (world->objects_array[i] == nullptr) {
			world->objects_array[i] = obj;
			i = MAX_OBJECTS;
		}
	}
}

bool ModulePhysics::DeleteObject(Object* obj) {
	bool ret = false;

	for (int i = 0; i < MAX_OBJECTS; i++) {
		if (obj == world->objects_array[i]) {
			delete world->objects_array[i]; //if there is something, delete it
			world->objects_array[i] = nullptr; //clear the pointer
			ret = true;
		}
	}
	return ret;
}

int ModulePhysics::FindObject(Object& obj) {

	int ret = -1;

	for (int i = 0; i < MAX_OBJECTS; i++) {
		if (obj == *world->objects_array[i]) {
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

			Object* obj = world->objects_array[i];
			SDL_DRect objRect = { obj->pos.x - obj->radius, obj->pos.y - obj->radius, (obj->radius*2), (obj->radius*2) };
			SDL_DPoint mousePoint = { position.x, position.y};

			if (SDL_DPointInRect(mousePoint, objRect))
			{
				return i;
			}
		}
	}

	return -1;
}
