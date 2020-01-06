#include "Application.h"
#include "Globals.h"
#include "p2Point.h"
#include "Module.h"

struct Object;

class ModuleScene : public Module
{

public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void MouseJointLogic();
	void TargetLogic();
	bool TargetExists();
	void ResetTarget();
	Object* Target();

private:
	bool mouse_joint;
	Object* target;
	int body_index;
};