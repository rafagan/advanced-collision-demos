#include "BitmaskExample.h"
#include "../DrawUtils.h"
#include "../Actor.h"
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
	// Other images to test the bitmask collision
	actor1 = Actor(0, 0, {}, 0.5f); actor1.init("quad.png", [](ofVec4f color) -> bool { return color.x == 0 && color.y == 0 && color.z == 0; });
	
	//[](ofVec4f color) -> bool { return color.distanceSquared(ofVec4f(255, 255, 255, 255)) < pow(10, 2); }
	actor2 = Actor(0, 0, {}, 0.5); actor2.init("circ_white.png", [](ofVec4f color) -> bool { return color.y == 255; });
	//actor1 = Actor(0, 0, {}, 1); actor1.init("fight.png");

	// Interesting example with animation
	//actor1 = Actor(2456 / 8, 230, { 0, 1, 2, 3, 4, 5, 6, 7 }, 0.5f); actor1.init("cavaloStripe.png");
	//actor2 = Actor(100, 100, { 0, 1, 2, 3, 4, 5, 4, 3, 2, 1 }, 0.1f); actor2.init("ufo_1x6.png");

	actor1.setPosition(Vector2D(600, 400));
}

void BitmaskExample::update()
{
	actor2.setPosition(Vector2D(ofGetMouseX(), ofGetHeight() - ofGetMouseY()));
	
	actor1.update();
	actor2.update();

	!actor1.testCollision(actor2) ?
		actor2.setColor(Vector3D(255, 255, 255)) :
		actor2.setColor(Vector3D(255, 255, 0));
}

void BitmaskExample::draw()
{
	actor2.draw();
	actor1.draw();
	actor2.drawIntersection(actor1);
}

void BitmaskExample::close()
{
}

IScreen* BitmaskExample::nextScreen()
{
	return this;
}
