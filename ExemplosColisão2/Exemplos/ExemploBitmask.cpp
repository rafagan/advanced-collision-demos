#include "ExemploBitmask.h"

#include "../Math/MathIncluder.h"

using namespace math;

ExemploBitmask::ExemploBitmask()
{}

void ExemploBitmask::init()
{
	keys = C2D2_PegaTeclas();
	mouse = C2D2_PegaMouse();

	//actor1 = new Actor("quad.png", 0, 0, {}, 0.5);
	//actor2 = new Actor("circ_white.png", 0, 0, {}, 0.5);
	//actor1 = new Actor("fight.png", 0, 0, {}, 1);

	actor1 = new Actor("cavaloStripe.png", 2456 / 8, 230, {0, 1, 2, 3, 4, 5, 6, 7}, 0.5f);
	actor2 = new Actor("ufo_1x6.png", 100, 100, {0, 1, 2, 3, 4, 5, 4, 3, 2, 1}, 0.1f);

	actor1->setPosition(Vector2D(600, 400));
}

void ExemploBitmask::update(const float dt)
{
	!actor1->testCollision(*actor2) ? actor2->setColor(Vector3D(255,255,255)) : actor2->setColor(Vector3D(255,0,0));
	actor2->setPosition(Vector2D((float) mouse->x,(float) mouse->y));
	actor1->update(dt);
	actor2->update(dt);
}

void ExemploBitmask::draw()
{
	actor1->draw();
	actor2->draw();
	actor2->drawIntersection(*actor1);
}

void ExemploBitmask::close()
{
	delete actor1;
	delete actor2;
}

IScreen* ExemploBitmask::nextScreen()
{
	return this;
}

ExemploBitmask::~ExemploBitmask()
{}
