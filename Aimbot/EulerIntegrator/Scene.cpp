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

	body_index = -1;
	mouse_joint = false;
	target = { NULL, NULL };
	
	return true;
}



update_status ModuleScene::Update(float dt) {

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) { //resets gravity to its default value
		App->physics->world->ChangeGravity(GRAVITY);
	}

	MouseJointLogic();
	TargetLogic();
	

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
	if (App->input->GetMouseButton(3) == KEY_DOWN) {
		Object* newObj = nullptr;
		newObj = new Object({ PIXEL_TO_METERS(App->input->GetMouseX()),PIXEL_TO_METERS(App->input->GetMouseY()) }, 0.5f, { 0,0 }, { 0,0 }, 150, 0.75f, false, "Ball");
		App->physics->AddObject(newObj);
	}

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp() {

	LOG("Scene CleanUp has been called");
	return true;

}

void ModuleScene::MouseJointLogic() {

	dPoint mouse_pos(App->input->GetMouseX(), App->input->GetMouseY());

	// Creates the mouse joint
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {
		body_index = App->physics->IsInsideObject(mouse_pos);
		if (body_index != -1) {
			mouse_joint = true;
		}
	}

	// Moves the object towards the mouse
	else if (mouse_joint == true && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
		dPoint speed;
		speed.x = (PIXEL_TO_METERS(mouse_pos.x) - App->physics->world->objects_array[body_index]->pos.x) / 20;
		speed.y = (PIXEL_TO_METERS(mouse_pos.y) - App->physics->world->objects_array[body_index]->pos.y) / 20;
		App->physics->world->objects_array[body_index]->speed += speed;
		App->renderer->DrawLine(mouse_pos.x, mouse_pos.y, METERS_TO_PIXELS(App->physics->world->objects_array[body_index]->pos.x), METERS_TO_PIXELS(App->physics->world->objects_array[body_index]->pos.y), 70, 70, 70);
	}

	// Restores previous conditions when mouse stops being pressed
	else if (mouse_joint == true && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP) {
		mouse_joint = false;
	}

}

void ModuleScene::TargetLogic() {
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && mouse_joint == false) {
		target.x = App->input->GetMouseX();
		target.y = App->input->GetMouseY();
	}
	if (target.x != NULL && target.y != NULL) { 
		App->renderer->DrawCircle(target.x, target.y, 5, 0, 0, 255); 
	}
}

bool ModuleScene::TargetExists() {
	if (target.x != NULL && target.y != NULL) { return true; }
	return false;
}

iPoint ModuleScene::Target() { return target; }
