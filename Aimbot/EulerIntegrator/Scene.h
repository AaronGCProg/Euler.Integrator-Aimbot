#include "Application.h"
#include "Globals.h"
#include "p2Point.h"
#include "Module.h"


class ModuleScene : public Module
{

public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void MouseJointLogic();
	bool GetMouseJointActive();

private:
	bool mouseJoint;
	
	int bodyIndex;
};