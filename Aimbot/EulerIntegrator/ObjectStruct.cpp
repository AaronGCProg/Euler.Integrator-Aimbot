#include "ObjectStruct.h"

Object::Object() {

	pos = { 0, 0 };
	speed = { 0, 0 };
	force = { 0, 0 };
	mass = 1;
	name = "";
	friction_coefficient = 0.5;
	radius = 0;
}


Object::Object(dPoint aPos, double radius, dPoint aSpeed, dPoint aforce, double aMass, double afriction_coefficient, p2SString aName) {

	pos = aPos;
	speed = aSpeed;
	force = aforce;
	mass = aMass;
	name = aName;
	this->radius = radius;
	friction_coefficient = afriction_coefficient;

}



double Object::CalculateAerodinamicCoeficientY() {

	return 0.5 * 1.225 * (double)speed.y * (double)speed.y * radius * AERODINAMIC_COEFICIENT;
}


double Object::CalculateAerodinamicCoeficientX() {

	return 0.5 * 1.225 * (double)speed.x * (double)speed.x * radius * AERODINAMIC_COEFICIENT;
}

bool Object::CheckCollision(const Object obj) const
{
	return !((this->pos.x + this->radius*2 < obj.pos.x || obj.pos.x + obj.radius*2 < this->pos.x) || (this->pos.y + this->radius*2 + PIXEL_TO_METERS(1) < obj.pos.y || obj.pos.y + obj.radius*2 + PIXEL_TO_METERS(1) < this->pos.y));
}


bool Object::operator==(Object& dt) const {

	bool ret = true;

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
	if (this->radius != dt.radius)
	{
		ret = false;
	}
	return ret;
}


void Object::AddForce(dPoint aForce) {
	force += aForce;
}


void Object::ResetForces()
{
	force = { 0,0 };
}


Object::~Object() {

	name.Clear();
}