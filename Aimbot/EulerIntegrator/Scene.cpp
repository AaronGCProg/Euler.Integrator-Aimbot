#include "Scene.h"
#include "Physics.h"
#include "Window.h"
#include "Application.h"
#include "Input.h"
#include "Application.h"
#include "Render.h"
#include "Collisions.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	LOG("Contructor of Module Scene has been called");
}

// Destructor
ModuleScene::~ModuleScene()
{
	LOG("Destructor of Module Scene has been called");
}

bool ModuleScene::Start() {
	LOG("Module Scene succesful Start()");

	bodyIndex = -1;
	mouseJoint = false;
	
	
	return true;
}



update_status ModuleScene::Update(float dt) {

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) { //resets gravity to its default value
		App->physics->world->ChangeGravity(GRAVITY);
	}

	MouseJointLogic();
	

	// lets you modify the world gravity with WASD keys
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		App->physics->world->AddGravity(-1, 0);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		App->physics->world->AddGravity(1, 0);
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		App->physics->world->AddGravity(0, 1);
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		App->physics->world->AddGravity(0, -1);
	}
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		App->collisions->ChangeCollBetweenObj();
	}


	//spawns new cube
	if (App->input->GetMouseButton(3) == KEY_DOWN) 
	{
		Object* newObj = nullptr;
		newObj = new Object({ PIXEL_TO_METERS(App->input->GetMouseX()),PIXEL_TO_METERS(App->input->GetMouseY()) }, 0.5f, { 0,0 }, { 0,0 }, 150, 0.75f, false, COLLISION_FRONT, "Ball");
		App->physics->AddObject(newObj);
	}

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp() 
{
	LOG("Scene CleanUp has been called");
	return true;

}

void ModuleScene::MouseJointLogic() 
{
	dPoint mousePos(App->input->GetMouseX(), App->input->GetMouseY());

	// Creates the mouse joint
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {

		bodyIndex = App->physics->IsInsideObject(mousePos);

		if (bodyIndex != -1 && App->physics->world->objects_array[bodyIndex]->noPhys == false) {
			
			mouseJoint = true;
		}
	}

	// Moves the object towards the mouse
	else if (mouseJoint == true && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
		dPoint speed;
		speed.x = (PIXEL_TO_METERS(mousePos.x) - App->physics->world->objects_array[bodyIndex]->pos.x) / 20;
		speed.y = (PIXEL_TO_METERS(mousePos.y) - App->physics->world->objects_array[bodyIndex]->pos.y) / 20;
		App->physics->world->objects_array[bodyIndex]->speed += speed;
		App->renderer->DrawLine(mousePos.x, mousePos.y, METERS_TO_PIXELS(App->physics->world->objects_array[bodyIndex]->pos.x), METERS_TO_PIXELS(App->physics->world->objects_array[bodyIndex]->pos.y), 70, 70, 70);
	}

	// Restores previous conditions when mouse stops being pressed
	else if (mouseJoint == true && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP) {
		mouseJoint = false;
	}

}

bool ModuleScene::GetMouseJointActive() {

	return mouseJoint;
}