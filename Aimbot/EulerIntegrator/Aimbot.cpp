#include "Aimbot.h"
#include "Application.h"
#include "Physics.h"
#include "Scene.h"

ModuleAimbot::ModuleAimbot(Application* app, bool start_enabled) : Module(app, start_enabled) {}

ModuleAimbot::~ModuleAimbot() {}

bool ModuleAimbot::Start() {
	double radius = 0.5f;
	aimbot = new Object({ 5.0f, SCREEN_HEIGHT - radius }, radius, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 5.0f, 0.1f, false, "aimbot");
	App->physics->AddObject(aimbot);
	state = AIMBOT_INITIAL_STATE;
	return true;
}

update_status ModuleAimbot::Update() {

	switch (state) {
	case AIMBOT_INITIAL_STATE:
		if (App->scene->TargetExists()) {
			dPoint fPosition = { (double) App->scene->Target().x, (double) App->scene->Target().y};
			dPoint iSpeed = CalculateTrajectory(aimbot->pos, fPosition);
		}
		break;
	case AIMBOT_SHOOTING:

		break;
	case AIMBOT_TARGET_IMPACT:

		break;
	default:
		break;
	}

	return UPDATE_CONTINUE;
}

bool ModuleAimbot::CleanUp() {

	return true;
}

dPoint ModuleAimbot::CalculateTrajectory(dPoint& iPosition, dPoint& fPosition) {

}
