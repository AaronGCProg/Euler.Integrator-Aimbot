#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "p2SString.h"

struct Object;

#define COEFFICIENT_OF_RESTITUTION 0.5

struct square {
	square(int X, int Y, int W, int H)
	{
		x = X;
		y = Y;
		w = W;
		h = H;
	};

	square() {};

	float x = 0.0f;
	float y = 0.0f;
	float w = 0.0f;
	float h = 0.0f;
};

// Module --------------------------------------
class ModuleCollisions : public Module
{
public:
	ModuleCollisions(Application* app, bool start_enabled = true);
	~ModuleCollisions();

	bool Start();
	update_status Update();
	bool CleanUp();

	void ForwardPropagation(Object* object1, Object* object2);

private:

};
