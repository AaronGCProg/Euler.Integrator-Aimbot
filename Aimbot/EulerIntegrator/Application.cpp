#include "Module.h"
#include "Application.h"
#include "Physics.h"
#include "Collisions.h"
#include "p2List.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Input.h"
#include "Aimbot.h"
//include header of all existing modules

Application::Application()
{

	renderer = new ModuleRender(this);
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	physics = new ModulePhysics(this);
	collisions = new ModuleCollisions(this);
	scene = new ModuleScene(this);
	aimbot = new ModuleAimbot(this);

	gameTimer = new j1Timer();
	gamePerfTimer = new j1PerfTimer();
	lastSecFrames = new j1Timer();

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules (reverse order for cleanUp)
	AddModule(window);
	AddModule(physics);
	AddModule(collisions);
	AddModule(input);
	AddModule(aimbot);
	AddModule(scene);

	//Renderer
	AddModule(renderer);

}

//Destructor of aplication, it calls all module destructors
Application::~Application()
{
	p2List_item<Module*>* item = list_modules.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->prev;
	}
}

bool Application::Init()
{
	bool ret = true;

	capTime = 60u;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		if (item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}

	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Module*>* item = list_modules.getFirst();

	PrepareUpdate();
	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		if (item->data->IsEnabled())
			ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		if (item->data->IsEnabled())
			ret = item->data->Update(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		if (item->data->IsEnabled())
			ret = item->data->PostUpdate();
		item = item->next;
	}

	FinishUpdate();

	return ret;
}

void Application::PrepareUpdate()
{
	frame_count++;
	last_second_frame_count++;

	//Controls pause of the game
	dt = lastFrameTimer.ReadSec();

	if (dt > 0.16f)
		dt = 0.16f;

	lastFrameTimer.Start();

}

void Application::FinishUpdate()
{
	// Amount of time since game start (use a low resolution timer)
	float seconds_since_startup = gameTimer->ReadSec();

	// Average FPS for the whole game life
	avg_fps = float(frame_count) / seconds_since_startup;

	// Amount of ms took the last update
	last_frame_ms = lastFrameTimer.Read();

	// Amount of frames during the last second
	if (lastSecFrames->Read() >= 1000)
	{
		frames_on_last_update = last_second_frame_count;
		last_second_frame_count = 0;
		lastSecFrames->Start();
	}

	if (last_frame_ms < 1000 / capTime)
	{
		SDL_Delay((1000 / capTime) - last_frame_ms);
	}

	//Title shown in the window
	p2SString title("%s-%s || FPS: %i Av.FPS: %.2f || Target FPS: %i || Last Frame Ms: %u ",
		TITLE, ORGANIZATION,
		frames_on_last_update, avg_fps,
		capTime,
		last_frame_ms);

	window->SetTitle(title.GetString());

}

//Calls all modules CleanUp()
bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}