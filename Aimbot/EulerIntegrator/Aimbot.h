#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"


struct Object;

enum Aimbot_States {
	AIMBOT_INITIAL_STATE,
	AIMBOT_SHOOTING,
	AIMBOT_TARGET_IMPACT
};

// Module --------------------------------------
class ModuleAimbot : public Module
{
public:
	ModuleAimbot(Application* app, bool start_enabled = true);
	~ModuleAimbot();

	bool Start();
	update_status Update();
	bool CleanUp();

	dPoint CalculateTrajectory(dPoint& iPosition, dPoint& fPosition);

private:
	Aimbot_States state;
	Object* aimbot;
};
