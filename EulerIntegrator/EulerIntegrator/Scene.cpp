#include "Scene.h"
#include "Physics.h"
#include "Window.h"
#include "Application.h"
#include "Input.h"


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
	ground = new Object({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 }, 200, 200, { 0,0 }, { 0,0 }, 1, 1, "EL TERRAH");
	App->physics->AddObject(*ground);

	return true;
}


update_status ModuleScene::PreUpdate()
{



	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt) {

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		App->physics->world->ChangeGravity(-9.81, 0);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		App->physics->world->ChangeGravity(9.81, 0);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		App->physics->world->ChangeGravity(0, 9.81);
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		App->physics->world->ChangeGravity(0, -9.81);
	}
	if (App->input->GetMouseButton(3) == KEY_REPEAT)
	{
		Object* lol = nullptr;
		lol = new Object({ PIXEL_TO_METERS(App->input->GetMouseX()),PIXEL_TO_METERS(App->input->GetMouseY())}, 1, 1, { 0,0 }, { 0,0 }, 20, 0.9, "EL TERRAH");
		App->physics->AddObject(*lol);
	}



	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate()
{



	return UPDATE_CONTINUE;
}


bool ModuleScene::CleanUp() {

	//Destroy world
	//Clear all pointers
	//Clear all arrays

	LOG("Scene CleanUp has been called");
	return true;

}