#include "AABBRotationExample.h"
#include "DrawUtils.h"
#include <ofAppNoWindow.h>

using namespace math;

AABBRotationExample::AABBRotationExample()
{
}


AABBRotationExample::~AABBRotationExample()
{
}

void AABBRotationExample::init()
{
	actor = new Actor("quad.png", 0, 0, {});
	actor->setPosition(ofGetWidth() / 2, ofGetHeight() / 2);
}

void AABBRotationExample::update()
{
	actor->update();
}

void AABBRotationExample::draw()
{
	actor->draw();
}

void AABBRotationExample::close()
{
	delete actor;
}

IScreen* AABBRotationExample::nextScreen()
{
	return this;
}
