#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"

// Module --------------------------------------
class ModuleAimbot : public Module
{
public:
	ModuleAimbot(Application* app, bool start_enabled = true);
	~ModuleAimbot();

	bool Start();
	update_status Update();
	bool CleanUp();

private:

};
