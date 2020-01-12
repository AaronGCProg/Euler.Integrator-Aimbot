#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Module.h"
#include "p2SString.h"

struct Object;

// Module --------------------------------------
class ModuleCollisions : public Module
{
public:
	ModuleCollisions(Application* app, bool start_enabled = true);
	~ModuleCollisions();

	bool CleanUp();

	void OnCollision(Object* c1);

	void ChangeCollBetweenObj();

	void CheckBorderCollision(Object* object);

private:
	void ResolveCollision(Object* c1, Object* c2);

	bool collBewtweenObjectsActive;
};
