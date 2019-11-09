#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "p2SString.h"
// Module --------------------------------------
//each object has a name, position, velocity and mass. It also has a force, which is set to 0 at the start of every loop
struct Object {

	p2SString name;
	dPoint pos;
	dPoint speed;
	dPoint force;
	double mass;

	//Collision Control
	collision_type category; //In which "collisions state" is the object located
	collision_type mask; //Which "collisions states" can he interact with

	Object() {

		pos = { 0, 0 };
		speed = { 0, 0 };
		force = { 0, 0 };
		mass = 1;
		name = "";

		category = COLL_ALL;
		mask = COLL_ALL;
	}

	Object(dPoint aPos, dPoint aSpeed, dPoint aforce, double aMass, p2SString aName) {

		pos = aPos;
		speed = aSpeed;
		force = aforce;
		mass = aMass;
		name = aName;

		category = COLL_ALL;
		mask = COLL_ALL;
	}

	Object(dPoint aPos, dPoint aSpeed, dPoint aforce, double aMass, p2SString aName, collision_type cat, collision_type Mask) {

		pos = aPos;
		speed = aSpeed;
		force = aforce;
		mass = aMass;
		name = aName;

		category = cat;
		mask = Mask;
	}

	bool CheckCollisionRect(const Object& obj) const;


	~Object() {};

};

struct World
{
	dPoint gravity;

	p2SString name;

	p2List<Object*>* objects_list;

	World()
	{
		name = "";
		gravity = { 0,9.81f };
		objects_list = new p2List<Object*>;
	}

	World(dPoint aGravity, p2SString aName)
	{
		gravity = aGravity;
		name = aName;
		objects_list = new p2List<Object*>;

	}
	~World() {}
};

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status Update();
	bool CleanUp();

	//Temp var to test collisions
	World* world;

private:

	
};






class ModuleIntegrator //Module Integrator? Why is this a module and not a function call in Module Physics? -Adrià
{						
public:
	ModuleIntegrator();
	~ModuleIntegrator();


private:
	void Integrate(Object &object, dPoint gravity);
	World world;
};











