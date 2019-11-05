
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"


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
};

class ModuleIntegrator
{
public:
	ModuleIntegrator();
	~ModuleIntegrator();


private:
	void Integrate(Object &object, dPoint gravity);


};











