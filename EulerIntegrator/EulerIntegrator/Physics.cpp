#include "Physics.h"
#include "Render.h"
#include "Application.h"


ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	LOG("Contructor of Module Physics has been called");
}

// Destructor
ModulePhysics::~ModulePhysics()
{
	LOG("Destructor of Module Physics has been called");
}

update_status ModulePhysics::Update() {

	//Here goes a call of Integrate() to all objects of the world
	p2List_item<Object*>*item = world->objects_list->start;
	while (item!=NULL)
	{
		Integrate(*item->data, world->gravity);
		item = item->next;
	}
	return UPDATE_CONTINUE;

}

update_status ModulePhysics::PostUpdate()
{
	p2List_item<Object*>* item = world->objects_list->start;
	while (item != NULL)
	{
		App->renderer->DrawQuad(item->data->rect, 255, 0 ,0, 255, false, false);
		item = item->next;
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
	LOG("Physics CleanUp has been called");
	return true;

}


void ModulePhysics::Integrate(Object& object, dPoint gravity)
{
	dPoint acc;

	acc.x = object.force.x * (1 / object.mass);
	acc.y = object.force.y * (1 / object.mass);

	object.speed.x += acc.x;
	object.speed.y += acc.y; //60 fps, one iteration

	object.pos.x += object.speed.x;
	object.pos.y += object.speed.y;
}
