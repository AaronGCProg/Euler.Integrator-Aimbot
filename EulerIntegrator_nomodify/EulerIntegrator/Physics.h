#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "p2SString.h"
#include "Application.h"




#define AERODINAMIC_COEFICIENT 1.05
#define RESTITUTION_COEFICIENT 0.9

#define GRAVITY {0,9.81f}

// Module --------------------------------------
//each object has a name, position, velocity and mass. It also has a force, which is set to 0 at the start of every loop
struct Object {
	
public:
	dPoint force; //In newtons WARNING, DO NOT ACCES THE VARIABLE WITHOUT EXPLICIT PERMISSION FROM THE PHYSICS GUYS, IF YOU NEED TO ADD A FORCE USE THE FUNCTION .AddForce()
	p2SString name;
	dPoint pos; //In meters
	dPoint speed;  //In meters/second
	double w, h; //In meters
	double mass; //In kg
	double friction_coefficient;


	//Collision Control
	movement_type type; //In which "collisions state" is the object located

	//Diferent object constructors
	Object() {

		pos = { 0, 0 };
		speed = { 0, 0 };
		force = { 0, 0 };
		mass = 1;
		name = "";
		friction_coefficient = 0.5;
		w = 0;
		h = 0;
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
		friction_coefficient = afriction_coefficient;

		if (mass==0)
			type = COLL_STATIC;
		else
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

		type = cat;
	}


	//Check if this object is colliding with anothe object
	bool CheckCollisionRect(Object& obj);

	//Functions to calculate aerodinamic coeficients
	double CalculateAerodinamicCoeficientY() {

		return 0.5 * 1.225 * (double)speed.y * (double)speed.y * w * AERODINAMIC_COEFICIENT;
	}

	double CalculateAerodinamicCoeficientX() {

		return 0.5 * 1.225 * (double)speed.x * (double)speed.x * h * AERODINAMIC_COEFICIENT;
	}

	//Overloaded operator to compare objects
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

	//Funcions to set forces into objects
	void AddForce(dPoint aForce){
		force += aForce;
	}
	void ResetForces()
	{
		force = { 0,0 };
	}

	~Object() {};

};

//Contains all objects created and apllies its gravity to them
struct World
{
	dPoint gravity;

	p2SString name;

	//p2List<Object*>* objects_list;
	//Objects array
	Object** objects_array;
	int index = 0;


	World()
	{
		objects_array = new Object*[MAX_OBJECTS];
		memset(objects_array, NULL, MAX_OBJECTS*sizeof(Object*));
		name = "";
		gravity = GRAVITY;
	}

	World(dPoint aGravity, p2SString aName)
	{
		objects_array = new Object*[MAX_OBJECTS];

		memset(objects_array, NULL, MAX_OBJECTS * sizeof(Object*));

		gravity = aGravity;
		name = aName;

	}
	~World() {}

	void ChangeGravity(double gravX, double gravY) {

		gravity.x = gravX;
		gravity.y = gravY;
	}
	void ChangeGravity(dPoint grav) {

		gravity = grav;
	}
	void AddGravity(double gravX, double gravY) {

		gravity.x += gravX;
		gravity.y += gravY;
	}
};

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
	void AddObject(Object& obj); //Adds object to the world list
	bool DeleteObject(Object& obj);
	int IsInsideObject(dPoint& position);	// returns the object array's position or -1
	int FindObject(Object& obj); //returns pos in array if found, -1 if not

	//Temp var to test collisions
	World* world;
	
};












