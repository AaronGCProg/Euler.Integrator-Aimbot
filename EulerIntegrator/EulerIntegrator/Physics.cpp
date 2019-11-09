#include "Physics.h"


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




//If (please do) Module Integrator gets absorbed by Module Physics, change accordingly all of the below

ModuleIntegrator::ModuleIntegrator()
{
}


ModuleIntegrator::~ModuleIntegrator()
{
}


void ModuleIntegrator::Integrate(Object& object, dPoint gravity)
{
	dPoint acc;

	acc.x = object.force.x * (1 / object.mass);
	acc.y = object.force.y * (1 / object.mass);

	object.speed.x += acc.x;
	object.speed.y += acc.y; //60 fps, one iteration

	object.pos.x += object.speed.x;
	object.pos.y += object.speed.y;
}
