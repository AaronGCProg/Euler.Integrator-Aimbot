#include "Application.h"
#include "Globals.h"
#include "Module.h"

class ModuleScene : public Module
{

public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Awake();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


private:

};