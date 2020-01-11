#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "Trajectory.h"

struct Object;



enum class AimbotStates {
	AIMBOT_IDLE,
	AIMBOT_CALCULATE_MONTECARLO,
	AIMBOT_CALCULATED_MONTECARLO,
	AIMBOT_SHOOT,
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

	Object* GetTarget();

private:
	void HandleInput();
	Trajectory CalculateTrajectory();
	void TargetLogic();
	bool TargetExists();
	void DeleteTarget();
	void CreateTarget();
	
	void ResetProjectile();

private:
	AimbotStates state;
	Trajectory trajectory;

	Object* aimbot;
	Object* propagationObj;

	Object* target;
};

