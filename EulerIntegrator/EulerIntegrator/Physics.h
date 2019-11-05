
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"

//each object has a name, position, velocity and mass. It also has a force, which is set to 0 at the start of every loop
struct Object {

	p2SString name;
	dPoint pos;
	dPoint speed;
	dPoint force;
	double mass;

	Object() {

		pos = { 0, 0 };
		pos = { 0, 0 };
		speed = { 0, 0 };
		force = { 0, 0 };
		mass = 1;
		name = "";

	}

	Object(dPoint aPos, dPoint aSpeed, dPoint aforce, double aMass, p2SString aName) {

		pos = aPos;
		speed = aSpeed;
		force = aforce;
		mass = aMass;
		name = aName;
	}

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
		gravity = { 0,9.81 };
		objects_list = new p2List<Object*>;
	}

	World(dPoint aGravity,p2SString aName)
	{
		gravity = aGravity;
		name = aName;
		objects_list = new p2List<Object*>;

	}
	~World(){}
};

class ModuleIntegrator
{
public:
	ModuleIntegrator();
	~ModuleIntegrator();


private:
	void Integrate(Object &object, dPoint gravity);
	World world;
};











