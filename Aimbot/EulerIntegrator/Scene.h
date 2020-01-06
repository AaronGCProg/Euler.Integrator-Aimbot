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
	bool TargetExists();

	iPoint Target();
private:
	void MouseJointLogic();
	void TargetLogic();

private:
	bool mouse_joint;
	iPoint target;
	int body_index;
};