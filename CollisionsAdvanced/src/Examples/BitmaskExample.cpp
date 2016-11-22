#include "BitmaskExample.h"
#include "../DrawUtils.h"
#include "../Actor.h"
#include <of3dGraphics.h>
#include <ofCamera.h>

using namespace math;

BitmaskExample::BitmaskExample()
{
}


BitmaskExample::~BitmaskExample()
{
}

void BitmaskExample::init()
{
	//actor1 = new Actor("quad.png", 0, 0, {}, 0.5);
	//actor2 = new Actor("circ_white.png", 0, 0, {}, 0.5);
	//actor1 = new Actor("fight.png", 0, 0, {}, 1);

	actor1 = Actor("cavaloStripe.png", 2456 / 8, 230, { 0, 1, 2, 3, 4, 5, 6, 7 }, 0.5f);
	actor2 = Actor("ufo_1x6.png", 100, 100, { 0, 1, 2, 3, 4, 5, 4, 3, 2, 1 }, 0.1f);

	actor1.setPosition(Vector2D(600, 400));
}

void BitmaskExample::update()
{
	!actor1.testCollision(actor2) ? 
		actor2.setColor(Vector3D(255, 255, 255)) : 
		actor2.setColor(Vector3D(255, 0, 0));

	actor2.setPosition(Vector2D(ofGetMouseX(), ofGetHeight() - ofGetMouseY()));
	
	actor1.update();
	actor2.update();
}

void BitmaskExample::draw()
{
	ofSetBackgroundColor(255, 255, 255);

	actor1.draw();
	//actor2.draw();
	//actor2.drawIntersection(actor1);
}

void BitmaskExample::close()
{
}

IScreen* BitmaskExample::nextScreen()
{
	return this;
}
