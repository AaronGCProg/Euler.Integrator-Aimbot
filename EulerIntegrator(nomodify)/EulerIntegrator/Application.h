#pragma once

#include "p2List.h"
#include "p2Defs.h"
#include "Globals.h"
#include "p2Log.h"
#include "p2List.h"
#include "Timer.h"
#include "PerfTimer.h"

class Module;
class ModulePhysics;
class ModuleCollisions;
class ModuleRender;
class ModuleWindow;
class ModuleInput;
class ModuleScene;


class Application
{
public:
	
	ModulePhysics* physics;
	ModuleCollisions* collisions;
	ModuleInput* input;
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleScene* scene;

	j1Timer* gameTimer = nullptr;
	j1PerfTimer* gamePerfTimer = nullptr;
	j1Timer* lastSecFrames = nullptr;
	j1Timer lastFrameTimer;


	uint64 frame_count = 0u;
	uint last_second_frame_count = 0u;

	uint32 last_frame_ms = 0u;
	uint32 frames_on_last_update = 0u;

	float avg_fps = 0.0f;
	float dt = 0.0f;

	uint capTime = 0u;


private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void FinishUpdate();
	void PrepareUpdate();


private:

	void AddModule(Module* mod);

};