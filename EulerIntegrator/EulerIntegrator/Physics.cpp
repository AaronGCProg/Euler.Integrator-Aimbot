#include "Physics.h"

Object::Object()
{

	pos = { 0,0 };
	speed = { 0,0 };
	mass = 1;
	name = "";

}
Object::Object(dPoint aPos, dPoint aSpeed, double aMass, p2SString aName)
{
	pos = aPos;
	speed = aSpeed;
	mass = aMass;
	name = aName;
}
Object::~Object() {};

void Object::SetName(p2SString aName)
{
	name = aName;
}
p2SString Object::GetName()
{
	return name;
}
void Object::SetPos(dPoint aPos)
{
	pos = aPos;
}
dPoint Object::GetPos()
{
	return pos;
}
void Object::SetSpeed(dPoint aSpeed)
{
	speed = aSpeed;
}
dPoint Object::GetSpeed()
{
	return speed;
}
void Object::SetMass(double aMass)
{
	mass = aMass;
}
double Object::GetMass()
{
	return mass;
}


void Integrate2(Object& object, dPoint force, double deltaT)
{
	dPoint acc;
	acc.x = force.x * (1 / object.);
	acc.y = force.y * (1 / object.mass);
	object.speed.x += acc.x * deltaT; //60 fps, one iteration
	object.speed.y += acc.y * deltaT; //60 fps, one iteration
	object.pos.x += object.speed.x * deltaT;
	object.pos.y += object.speed.y * deltaT;

}



/*void ForwardPropagation(float* xposition, float* xspeed, float* xground) {
	float x_aux;
	x_aux = (*xposition + *xspeed);
	if (x_aux < *xground) { *xposition = x_aux; }
	else { *xposition = *xground; }
}*/

