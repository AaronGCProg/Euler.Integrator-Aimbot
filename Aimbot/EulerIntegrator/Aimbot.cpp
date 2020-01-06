#include "Aimbot.h"
#include "Application.h"
#include "Physics.h"
#include "Scene.h"
#include <time.h>


#define MONTECARLO_ITERATION 100

ModuleAimbot::ModuleAimbot(Application* app, bool start_enabled) : Module(app, start_enabled) {}

ModuleAimbot::~ModuleAimbot() {}

bool ModuleAimbot::Start() {

	double radius = 0.5f;
	aimbot = new Object({ 5.0f, SCREEN_HEIGHT - radius }, radius, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 5.0f, 0.1f, false, "aimbot");
	App->physics->AddObject(aimbot);
	state = AimbotStates::AIMBOT_IDLE;
	return true;
}

update_status ModuleAimbot::Update() {

	switch (state) {

	case AimbotStates::AIMBOT_IDLE:

		break;

	case AimbotStates::AIMBOT_CALCULATE_MONTECARLO:
		if (App->scene->TargetExists()) {
			dPoint fPosition = { (double) App->scene->Target().x, (double) App->scene->Target().y};
			dPoint iSpeed = CalculateTrajectory(aimbot->pos, fPosition);
		}
		break;

	case AimbotStates::AIMBOT_SHOOT:

		break;

	case AimbotStates::AIMBOT_TARGET_IMPACT:

		break;
	
	case AimbotStates::AIMBOT_RESET:

		break;
	}

	return UPDATE_CONTINUE;
}

bool ModuleAimbot::CleanUp() {

	return true;
}

dPoint ModuleAimbot::CalculateTrajectory(dPoint& iPosition, dPoint& fPosition) {
	dPoint speed = { 0, 0 };	// This is just so that the functions compiles

	// MONTECARLO 
	int numbers[MONTECARLO_ITERATION];

	srand(time(NULL));

	for (int i = 0; i < MONTECARLO_ITERATION; i++) 
	{
		numbers[i] = rand() % 200 + 1;	// Generates number from 1 to 200
	}

	return speed;
}
