#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"


struct Object;

enum class AimbotStates {
	AIMBOT_IDLE,
	AIMBOT_CALCULATE_MONTECARLO,
	AIMBOT_SHOOT,
	AIMBOT_TARGET_IMPACT,
	AIMBOT_RESET
};

// Module --------------------------------------
class ModuleAimbot : public Module
{
public:
	ModuleAimbot(Application* app, bool start_enabled = true);
	~ModuleAimbot();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:
	void HandleInput();
	dPoint CalculateTrajectory(dPoint& iPosition, dPoint& fPosition);

private:
	AimbotStates state;
	Object* aimbot;
};


struct Trajectory
{
	dPoint speed;
	float angle;
};