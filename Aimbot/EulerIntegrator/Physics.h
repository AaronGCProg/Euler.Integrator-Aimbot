#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "p2SString.h"
#include "Application.h"
#include "World.h"


//Contains all objects created and apllies its gravity to them


class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate();
	bool CleanUp();
	void Integrate(Object &object, dPoint gravity,float dt); //Integrates objects
	void AddObject(Object* obj); //Adds object to the world list
	bool DeleteObject(Object& obj);
	int IsInsideObject(dPoint& position);	// returns the object array's position or -1
	int FindObject(Object& obj); //returns pos in array if found, -1 if not

	//Temp var to test collisions
	World* world;
	
};



