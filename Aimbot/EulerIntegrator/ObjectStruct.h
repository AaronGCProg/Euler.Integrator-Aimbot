#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "p2SString.h"
#include "Application.h"

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
	Object();

	Object(dPoint aPos, double width, double height, dPoint aSpeed, dPoint aforce, double aMass, double afriction_coefficient, p2SString aName);

	Object(dPoint aPos, double width, double height, dPoint aSpeed, dPoint aforce, double aMass, double afriction_coefficient, p2SString aName, movement_type cat);


	//Check if this object is colliding with anothe object
	bool CheckCollisionRect(Object& obj);

	//Functions to calculate aerodinamic coeficients
	double CalculateAerodinamicCoeficientY();

	double CalculateAerodinamicCoeficientX();

	//Overloaded operator to compare objects
	bool operator==(Object& dt) const;

	//Funcions to set forces into objects
	void AddForce(dPoint aForce);
	void ResetForces();

	~Object();

};