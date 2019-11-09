#include "Collisions.h"
#include"Application.h"
#include"Physics.h"

ModuleCollisions::ModuleCollisions(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	LOG("Contructor of Module Physics has been called");
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{
	LOG("Destructor of Module Physics has been called");
}

bool ModuleCollisions::Start()
{
	LOG("Module Collisions succesful Start()");

	return true;
}

update_status ModuleCollisions::Update() 
{
	Object* c1;
	Object* c2;

	for (p2List_item<Object*>* objIterator = App->physics->world->objects_list->start; objIterator != NULL; objIterator = objIterator->next)
	{
		c1 = objIterator->data;

		// avoid checking collisions already checked
		for (p2List_item<Object*>* objIterator2 = objIterator->next; objIterator2 != NULL; objIterator2 = objIterator2->next)
		{
			c2 = objIterator->data;

			//if (c1->CheckCollisionRect(*c2) == true)
			//{
			//	if (matrix[c1->type][c2->type] && c1->callback)
			//		c1->callback->OnCollision(c1, c2);

			//	if (matrix[c2->type][c1->type] && c2->callback)
			//		c2->callback->OnCollision(c2, c1);
			//}

		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleCollisions::CleanUp() 
{

	LOG("Collisions CleanUp has been called");
	return true;

}

// -----------------------------------------------------

bool Object::CheckCollisionRect(const Object& obj) const
{
	return !((this->pos.x /*+ this->rect.w*/ < obj.pos.x || obj.pos.x /*+ r.w*/ < this->pos.x) || (this->pos.y /*+ this->rect.h*/ < obj.pos.y || obj.pos.y /*+ r.h*/ < this->pos.y));
}

void ModuleCollisions::ForwardPropagation(dPoint* position, dPoint* speed, dPoint* ground) {
/*	dPoint position_aux;
	position_aux.x = (position->x + speed->x);
	position_aux.y = (position->y + speed->y);

	if (position_aux.x < ground->x || position_aux.x > ground->x + ground->w || position_aux.y < ground->y || position_aux.y > ground->y + ground->h) {
		position->x = position_aux.x;		// THIS FUNCTION WILL MOVE THE OBJECT IF NO COLLISION EXISTS
		position->y = position_aux.y;
	}

	else if (position_aux.x > ground->x && position->x < ground->x) {
		position->x = ground->x;	// CORRECTS A COLLISION IN THE LEFT SIDE OF THE GROUND
		speed->x *= -1;
	}

	else if (position_aux.x < ground->x + ground->w && position->x > ground->x + ground->w) {
		position->x = ground->x + ground->w;	// CORRECTS A COLLISION IN THE RIGHT SIDE OF THE GROUND
		speed->x *= -1;
	}

	else if (position_aux.y > ground->y && position->y < ground->y) {
		position->y = ground->y;	// CORRECTS A COLLISION IN THE UPPER SIDE OF THE GROUND
		speed->y *= -1;
	}

	else if (position_aux.y < ground->y + ground->h && position->y > ground->y + ground->h) {
		position->y = ground->y + ground->h;	// CORRECTS A COLLISION IN THE LOWER SIDE OF THE GROUND
		speed->y *= -1;
	}
	*/
}