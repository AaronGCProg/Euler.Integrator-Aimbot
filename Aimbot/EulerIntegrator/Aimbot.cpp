#include "Aimbot.h"
#include "Application.h"
#include "Physics.h"
#include "Scene.h"
#include "Collisions.h"
#include "Input.h"

#include <time.h>


#define MONTECARLO_ITERATION 100
#define PROPAGATION 100

ModuleAimbot::ModuleAimbot(Application* app, bool start_enabled) : Module(app, start_enabled) {}

ModuleAimbot::~ModuleAimbot() {}

bool ModuleAimbot::Start() {

	double radius = 0.5f;
	aimbot = new Object({ PIXEL_TO_METERS(SCREEN_WIDTH / 3), PIXEL_TO_METERS(SCREEN_HEIGHT - radius) }, radius, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 5.0f, 0.1f, false, "aimbot");
	App->physics->AddObject(aimbot);
	state = AimbotStates::AIMBOT_IDLE;

	double propagationRadius = 0.1f;
	propagationObj = new Object({ 5.0f, SCREEN_HEIGHT - propagationRadius }, propagationRadius, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 5.0f, 0.1f, false, "propagation");
	App->physics->AddObject(propagationObj);

	return true;
}

update_status ModuleAimbot::Update(float dt) {

	HandleInput();

	switch (state) {

	case AimbotStates::AIMBOT_IDLE:

		break;

	case AimbotStates::AIMBOT_CALCULATE_MONTECARLO:
		
		if (App->scene->TargetExists()) {
			//dPoint iSpeed = CalculateTrajectory(aimbot->pos, App->scene->Target()->pos);
			state = AimbotStates::AIMBOT_CALCULATED_MONTECARLO;

		}

		break;

	case AimbotStates::AIMBOT_CALCULATED_MONTECARLO:

		LOG("Ready to shoot baby");

		break;

	case AimbotStates::AIMBOT_SHOOT:

		break;

	case AimbotStates::AIMBOT_TARGET_IMPACT:
		App->scene->ResetTarget();
		App->physics->DeleteObject(propagationObj);
		propagationObj = nullptr;
		state = AimbotStates::AIMBOT_RESET;
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

// Trajectory with Montecarlo method
Trajectory ModuleAimbot::CalculateTrajectory(float speed, float angle) {

	Trajectory result;
	result.angle = 0;
	result.speed = 0;

	float seedSpeed[MONTECARLO_ITERATION];
	float seedAngle[MONTECARLO_ITERATION];

	srand(time(NULL));

	for (int i = 0; i < MONTECARLO_ITERATION; i++) 
	{
		seedSpeed[i] = rand() % 200 + 1;	
		seedAngle[i] = rand() % 180 + 1;

		for (int j = 0; j < PROPAGATION; j++)
		{
			App->physics->Integrate(*propagationObj, GRAVITY, App->dt);

			/* DESCOMENTAR AL PONER EL NOMBRE DEL OBJETO TARGET
			if (propagationObj->AccurateCheckCollision(App->scene->"PONER OBJETO TARGET")) 
			{
				
				result.angle = seedAngle[i];
				result.speed = seedSpeed[i];

				return result;
			}*/
		}
	}

	return result;
}
