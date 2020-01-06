#include "Aimbot.h"
#include "Application.h"
#include "Physics.h"
#include "Scene.h"
#include "Input.h"
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

update_status ModuleAimbot::Update(float dt) {

	HandleInput();

	switch (state) {

	case AimbotStates::AIMBOT_IDLE:

		break;

	case AimbotStates::AIMBOT_CALCULATE_MONTECARLO:
		
		if (App->scene->TargetExists()) {
			dPoint fPosition = { (double) App->scene->Target().x, (double) App->scene->Target().y};
			dPoint iSpeed = CalculateTrajectory(aimbot->pos, fPosition);
			state = AimbotStates::AIMBOT_CALCULATED_MONTECARLO;
		}

		break;

	case AimbotStates::AIMBOT_CALCULATED_MONTECARLO:

		LOG("Ready to shoot baby");

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


void ModuleAimbot::HandleInput() {

	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		state = AimbotStates::AIMBOT_CALCULATE_MONTECARLO;
	}

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
