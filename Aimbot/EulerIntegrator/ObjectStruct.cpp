#include "ObjectStruct.h"

Object::Object() :
	pos(0, 0),
	speed(0, 0),
	force(0, 0),
	mass(1),
	name(),
	frictionCoefficient(0.5),
	radius(0),
	noPhys(false)
{}


Object::Object(dPoint aPos, double radius, dPoint aSpeed, dPoint aforce, double aMass, double afriction_coefficient, bool noPhys, collision_flag collFlag, p2SString aName) :
	pos(aPos),
	speed(aSpeed),
	force(aforce),
	mass(aMass),
	name(aName),
	radius(radius),
	frictionCoefficient(afriction_coefficient),
	noPhys(noPhys),
	collFlag(collFlag)
{}


double Object::CalculateAerodinamicCoeficientY() {

	return 0.5 * 1.225 * (double)speed.y * (double)speed.y * radius * AERODINAMIC_COEFICIENT;
}


double Object::CalculateAerodinamicCoeficientX() {

	return 0.5 * 1.225 * (double)speed.x * (double)speed.x * radius * AERODINAMIC_COEFICIENT;
}

bool Object::QuickCheckCollision(const Object* obj) const
{
	return !(
		(this->pos.x + this->radius < (obj->pos.x - obj->radius))
		|| (obj->pos.x + obj->radius < (this->pos.x - this->radius))
		|| (this->pos.y + this->radius  < (obj->pos.y - obj->radius))
		|| (obj->pos.y + obj->radius < this->pos.y - obj->radius)
		 
		);
}

bool Object::AccurateCheckCollision(const Object* obj) const
{
	bool ret = false;

	double a = (pos.x) - (obj->pos.x);
	double b = (pos.y ) -(obj->pos.y);

	double distance = sqrt( (a*a) + (b*b) );

	if (distance < radius + obj->radius)
		ret = true;

	return ret;
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

void Object::SetSpeed(float speed, float angle) {

	angle = DEG_TO_RAD(angle);

	double xSpeed = speed * cos(angle);
	double ySpeed = speed * sin(angle);

	this->speed.x = xSpeed;
	this->speed.y = ySpeed;
}


void Object::ResetForces()
{
	force = { 0,0 };
}

void Object::ResetSpeed()
{
	speed = { 0,0 };
}


Object::~Object() {

	name.Clear();
}