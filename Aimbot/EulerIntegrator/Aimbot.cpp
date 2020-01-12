#include "Aimbot.h"
#include "Application.h"
#include "Physics.h"
#include "Scene.h"
#include "Collisions.h"
#include "Input.h"
#include "Render.h"

#include <time.h>


#define MONTECARLO_ITERATION 100
#define PROPAGATION 100

ModuleAimbot::ModuleAimbot(Application * app, bool start_enabled) : Module(app, start_enabled) {}

ModuleAimbot::~ModuleAimbot() {}

bool ModuleAimbot::Start() {

	double radius = 0.5f;
	aimbot = new Object({ PIXEL_TO_METERS(SCREEN_WIDTH / 3), PIXEL_TO_METERS(SCREEN_HEIGHT - radius) }, radius, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 5.0f, 0.1f, true, COLLISION_BACK, "aimbot");
	App->physics->AddObject(aimbot);
	state = AimbotStates::AIMBOT_IDLE;

	srand(time(NULL));

	target = nullptr;

	propagationObj = nullptr;

	return true;
}

update_status ModuleAimbot::Update(float dt) {

	HandleInput();

	switch (state) {

	case AimbotStates::AIMBOT_IDLE:

		break;

	case AimbotStates::AIMBOT_CALCULATE_MONTECARLO:

		if (propagationObj == nullptr) {
			double propagationRadius = 0.1f;
			propagationObj = new Object({ 5.0f, SCREEN_HEIGHT - propagationRadius }, propagationRadius, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 5.0f, 0.1f, false, COLLISION_FRONT, "propagation");
			App->physics->AddObject(propagationObj);
		}

		if (TargetExists()) {
			trajectory = CalculateTrajectory(dt);
			LOG("Ready to shoot, baby");
			propagationObj->pos.x = aimbot->pos.x;
			propagationObj->pos.y = aimbot->pos.y;
			state = AimbotStates::AIMBOT_CALCULATED_MONTECARLO;
		}

		break;

	case AimbotStates::AIMBOT_CALCULATED_MONTECARLO:

		for (int i = 0; i < MONTECARLO_ITERATION - 1; i++)
		{
			if (!(trajectory.trace[i + 1].x == -100 || trajectory.trace[i + 1].y == -100))
				App->renderer->DrawLine(trajectory.trace[i].x, trajectory.trace[i].y, trajectory.trace[i + 1].x, trajectory.trace[i + 1].y, 255, 0, 0, 255);				
		}

		//Do not log here. It does it every frame
		propagationObj->pos.x = aimbot->pos.x;
		propagationObj->pos.y = aimbot->pos.y;

		break;

	case AimbotStates::AIMBOT_SHOOT:

		propagationObj->SetSpeed(trajectory.speed, trajectory.angle);
		trajectory.angle = 0; trajectory.speed = 0;

		state = AimbotStates::AIMBOT_IDLE;
		break;
	}

	return UPDATE_CONTINUE;
}


void ModuleAimbot::HandleInput() {

	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {

		TargetLogic();

		ResetProjectile();
		
		state = AimbotStates::AIMBOT_CALCULATE_MONTECARLO;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && state == AimbotStates::AIMBOT_CALCULATED_MONTECARLO) {

		state = AimbotStates::AIMBOT_SHOOT;
	}
}


bool ModuleAimbot::CleanUp()
{
	aimbot = nullptr;
	propagationObj = nullptr;
	target = nullptr;

	return true;
}

// Trajectory with Montecarlo method
Trajectory ModuleAimbot::CalculateTrajectory(float dt) {

	dPoint auxPos = aimbot->pos;
	dPoint auxSpeed(0, 0);

	Trajectory result;
	Trajectory AuxResult;

	int TimeCompare = 100;
	int AuxTimeCompare = 100;


	for (int i = 0; i < MONTECARLO_ITERATION; i++)
	{
		bool outOfFor = false;

		float seedSpeed = 13 + rand() % 5;
		float seedAngle = 180 + rand() % 180;

		float seedAngleaux = DEG_TO_RAD(seedAngle);

		propagationObj->speed = { seedSpeed * cos(seedAngleaux), seedSpeed * sin(seedAngleaux) };
		propagationObj->pos = auxPos;

		for (int j = 0; j < PROPAGATION; j++)
		{
			
			App->physics->Integrate(*propagationObj, App->physics->world->gravity, dt);

			AuxResult.trace[j].x = METERS_TO_PIXELS(propagationObj->pos.x);
			AuxResult.trace[j].y = METERS_TO_PIXELS(propagationObj->pos.y);


			if (propagationObj->AccurateCheckCollision(target))
			{
				AuxResult.angle = seedAngle;
				AuxResult.speed = seedSpeed;
				AuxTimeCompare = j;

				if (AuxTimeCompare < TimeCompare) {
					result = AuxResult;
					TimeCompare = j;
				}
				outOfFor = true;
			}
		}
	}

	propagationObj->pos = auxPos;
	propagationObj->speed = auxSpeed;

	return result;
}


void ModuleAimbot::TargetLogic()
{
	if (App->scene->GetMouseJointActive() == false) {

		if (TargetExists())
			DeleteTarget();

		CreateTarget();
	}
}


bool ModuleAimbot::TargetExists() {

	if (target != nullptr) { return true; }
	return false;
}

Object* ModuleAimbot::GetTarget() {

	return target;
}


void ModuleAimbot::CreateTarget()
{

	dPoint position = { PIXEL_TO_METERS((double)App->input->GetMouseX()), PIXEL_TO_METERS((double)App->input->GetMouseY()) };
	target = new Object(position, 0.5f, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 10.0f, 0.1f, true, COLLISION_FRONT, "target");
	App->physics->AddObject(target);
}


void ModuleAimbot::DeleteTarget() {

	App->physics->DeleteObject(target);
	target = nullptr;
}


void ModuleAimbot::ResetProjectile() {

	if (propagationObj != nullptr) {

		App->physics->DeleteObject(propagationObj);
		propagationObj = nullptr;
	}
}