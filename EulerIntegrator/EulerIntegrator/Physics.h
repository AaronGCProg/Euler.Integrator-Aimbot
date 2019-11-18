#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "p2SString.h"
#include "Application.h"
// Module --------------------------------------
//each object has a name, position, velocity and mass. It also has a force, which is set to 0 at the start of every loop
struct Object {

	p2SString name;
	dPoint pos;
	dPoint speed;
	dPoint force;
	double w, h;
	double mass;
	SDL_Rect rect;
	double friction_coefficient;


	//Collision Control
	movement_type type; //In which "collisions state" is the object located
	collision current_collision;

	Object() {

		pos = { 0, 0 };
		speed = { 0, 0 };
		force = { 0, 0 };
		mass = 1;
		name = "";
		friction_coefficient = 0.5;
		w = 0;
		h = 0;
		rect = {0,0,0,0};

		type = COLL_DYNAMIC;
	}

	Object(dPoint aPos, double width, double height, dPoint aSpeed, dPoint aforce, double aMass, double afriction_coefficient, p2SString aName) {

		pos = aPos;
		speed = aSpeed;
		force = aforce;
		mass = aMass;
		name = aName;
		w = width;
		h = height;
		rect = { (int)aPos.x,(int)aPos.y,(int)width,(int)height };
		friction_coefficient = afriction_coefficient;

		type = COLL_DYNAMIC;
	}

	Object(dPoint aPos, double width, double height, dPoint aSpeed, dPoint aforce, double aMass, double afriction_coefficient, p2SString aName, movement_type cat) {

		pos = aPos;
		speed = aSpeed;
		force = aforce;
		mass = aMass;
		friction_coefficient = afriction_coefficient;
		name = aName;

		w = width;
		h = height;
		rect = { (int)aPos.x,(int)aPos.y,(int)width,(int)height };

		type = cat;
	}

	bool CheckCollisionRect(Object& obj);

	bool operator==(Object& dt) const {

		bool ret = true;

		if (this->h != dt.h)
		{
			ret = false;
		}
		
		if (this->mass != dt.mass)
		{
			ret = false;
		}
		if (this->name != dt.name)
		{
			ret = false;
		}
		if (this->pos != dt.pos)
		{
			ret = false;
		}
		if (this->speed != dt.speed)
		{
			ret = false;
		}
		if (this->w != dt.w)
		{
			ret = false;
		}
		return ret;
	}

	~Object() {};

};

struct World
{
	dPoint gravity;

	p2SString name;

	//p2List<Object*>* objects_list;
	Object** objects_array;
	int index = 0;


	World()
	{
		objects_array = new Object*[MAX_OBJECTS];
		memset(objects_array, NULL, MAX_OBJECTS);
		name = "";
		gravity = { 0,9.81f };
	}

	World(dPoint aGravity, p2SString aName)
	{
		objects_array = new Object*[MAX_OBJECTS];

		memset(objects_array, NULL, MAX_OBJECTS);

		gravity = aGravity;
		name = aName;
		

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
	update_status PostUpdate();
	bool CleanUp();
	void Integrate(Object &object, dPoint gravity);
	void AddObject(Object& obj);
	bool DeleteObject(Object& obj);
	int FindObject(Object& obj); //returns pos in array if found, -1 if not


	//Temp var to test collisions
	World* world;

private:

	
};












