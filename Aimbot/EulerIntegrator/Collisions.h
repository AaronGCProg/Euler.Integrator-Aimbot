#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "p2SString.h"

struct Object;

enum collisionDirection
{
	DIRECTION_NONE = -1,

	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_MAX
};


// Module --------------------------------------
class ModuleCollisions : public Module
{
public:
	ModuleCollisions(Application* app, bool start_enabled = true);
	~ModuleCollisions();

	bool CleanUp();

	void OnCollision(Object& object);

	void ChangeCollBetweenObj();
private:
	void ResolveCollision(Object* c1, Object* c2);
	int CheckCollisionDir(Object* c1, Object* c2);

	bool collBewtweenObjectsActive;
};
