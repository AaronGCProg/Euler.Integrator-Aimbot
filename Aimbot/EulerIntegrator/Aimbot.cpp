#include "Aimbot.h"
#include "Application.h"
#include "Physics.h"

ModuleAimbot::ModuleAimbot(Application* app, bool start_enabled) : Module(app, start_enabled) {

}

ModuleAimbot::~ModuleAimbot() {}

bool ModuleAimbot::Start() {
	double radius = 0.5f;
	App->physics->AddObject(new Object({5, SCREEN_HEIGHT-radius}, radius, { 0, 0 }, { 0, 0 }, 5, 0.1, false, "aimbot"));

	return true;
}

update_status ModuleAimbot::Update() {



	return UPDATE_CONTINUE;
}

bool ModuleAimbot::CleanUp() {

	return true;
}
