#include "Application.h"
#include "Globals.h"
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

private:
	bool mouse_joint;
	int body_index;
};