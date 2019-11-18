#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "p2SString.h"

struct Object;

enum collision {
	NONE_COLLISION,
	TOP_COLLISION,
	BOTTOM_COLLISION,
	LEFT_COLLISION,
	RIGHT_COLLISION,
	LAST_COLLISION
};

// Module --------------------------------------
class ModuleCollisions : public Module
{
public:
	ModuleCollisions(Application* app, bool start_enabled = true);
	~ModuleCollisions();

	bool Start();
	bool CleanUp();

	void OnCollision(Object& object);
	void ForwardPropagation(Object* object1, Object* object2);

private:

};
