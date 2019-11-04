
#include "Globals.h"
#include "p2Point.h"

class Object {
private:
	p2SString name;
	dPoint pos;
	dPoint speed;
	double mass;
public:
	Object();
	Object(dPoint aPos, dPoint aSpeed, double aMass, p2SString aName);
	~Object();

	void SetName(p2SString aName);
	p2SString GetName();
	void SetPos(dPoint aPos);
	dPoint GetPos();
	void SetSpeed(dPoint aSpeed);
	dPoint GetSpeed();
	void SetMass(double aMass);
	double GetMass();


};



//float Integrate(Object &object, int time);

void Integrate2(Object &object, dPoint force,double deltaT=(1/60));


