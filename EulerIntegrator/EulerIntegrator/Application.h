#pragma once

#include "p2List.h"
#include "p2Defs.h"
#include "Globals.h"
#include "p2Log.h"
#include "p2List.h"

class Module;
class ModulePhysics;


class Application
{
public:
	
	ModulePhysics* physics;
	


private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};