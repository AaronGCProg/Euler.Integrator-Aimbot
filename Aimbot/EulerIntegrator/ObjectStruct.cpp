#include "ObjectStruct.h"

Object::Object() {

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


Object::Object(dPoint aPos, double width, double height, dPoint aSpeed, dPoint aforce, double aMass, double afriction_coefficient, p2SString aName) {

	pos = aPos;
	speed = aSpeed;
	force = aforce;
	mass = aMass;
	name = aName;
	w = width;
	h = height;
	friction_coefficient = afriction_coefficient;

	if (mass == 0)
		type = COLL_STATIC;
	else
		type = COLL_DYNAMIC;
}


Object::Object(dPoint aPos, double width, double height, dPoint aSpeed, dPoint aforce, double aMass, double afriction_coefficient, p2SString aName, movement_type cat) {

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


bool Object::CheckCollisionRect(Object& obj)
{
	return !((this->pos.x + this->w < obj.pos.x || obj.pos.x + obj.w < this->pos.x) || (this->pos.y + this->h + PIXEL_TO_METERS(1) < obj.pos.y || obj.pos.y + obj.h + PIXEL_TO_METERS(1) < this->pos.y));
}


double Object::CalculateAerodinamicCoeficientY() {

	return 0.5 * 1.225 * (double)speed.y * (double)speed.y * w * AERODINAMIC_COEFICIENT;
}


double Object::CalculateAerodinamicCoeficientX() {

	return 0.5 * 1.225 * (double)speed.x * (double)speed.x * h * AERODINAMIC_COEFICIENT;
}


bool Object::operator==(Object& dt) const {

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