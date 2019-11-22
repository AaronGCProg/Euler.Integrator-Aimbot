#include "Scene.h"
#include "Physics.h"
#include "Window.h"
#include "Application.h"
#include "Input.h"
#include "Application.h"
#include "Render.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	LOG("Contructor of Module Scene has been called");
}

// Destructor
ModuleScene::~ModuleScene()
{
	LOG("Destructor of Module Scene has been called");
}


bool Awake()
{


	return true;
}


bool ModuleScene::Start() {
	LOG("Module Scene succesful Start()");



	Object* ground = nullptr;
	ground = new Object({ PIXEL_TO_METERS(0),PIXEL_TO_METERS(-SCREEN_HEIGHT + 18) }, PIXEL_TO_METERS(SCREEN_WIDTH), 2, { 0,0 }, { 0,0 }, 0, 0.9, "EL TERRAH");
	App->physics->AddObject(*ground);

	
	return true;
}


update_status ModuleScene::PreUpdate()
{



	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt) {

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) //resets gravity to its default value
	{
		App->physics->world->ChangeGravity(GRAVITY);
	}


	// lets you modify the world gravity with WASD keys
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		App->physics->world->AddGravity(-1, 0);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		App->physics->world->AddGravity(1, 0);
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		App->physics->world->AddGravity(0, 1);
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		App->physics->world->AddGravity(0, -1);
	}


	//spawns new cube
	if (App->input->GetMouseButton(3) == KEY_DOWN)
	{
		Object* lol = nullptr;
		lol = new Object({ PIXEL_TO_METERS(App->input->GetMouseX()),PIXEL_TO_METERS(App->input->GetMouseY()) }, 1, 1, { 0,0 }, { 0,0 }, 20, 0.9, "EL TERRAH");
		App->physics->AddObject(*lol);
	}



	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate()
{



	return UPDATE_CONTINUE;
}


bool ModuleScene::CleanUp() {

	LOG("Scene CleanUp has been called");
	return true;

}