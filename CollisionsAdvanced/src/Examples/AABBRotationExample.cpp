#include "AABBRotationExample.h"
#include "../DrawUtils.h"
#include <ofAppNoWindow.h>
#include "../EventManager.h"

using namespace math;

AABBRotationExample::AABBRotationExample(): actor(nullptr) 
{
}


AABBRotationExample::~AABBRotationExample()
{
}

void AABBRotationExample::init()
{
	actor = new Actor(0, 0, {});
	actor->init("quad.png");
	actor->setPosition(ofGetWidth() / 2, ofGetHeight() / 2);
}

void AABBRotationExample::update()
{
	float dt = ofGetLastFrameTime();

	if (EventManager::getKeyState(OF_KEY_RIGHT))
		actor->rotate(-toRadians(30 * dt));
	if (EventManager::getKeyState(OF_KEY_LEFT))
		actor->rotate(toRadians(30 * dt));
	if (EventManager::getKeyState(OF_KEY_UP))
		actor->scale(1 * dt);
	if (EventManager::getKeyState(OF_KEY_DOWN))
		actor->scale(-1 * dt);

	//Syntax sugar
	if (KEY('A'))
		actor->translate(Vector2D(-100, 0) * dt);
	if (KEY('D'))
		actor->translate(Vector2D(100, 0) * dt);
	if (KEY('W'))
		actor->translate(Vector2D(0, 100) * dt);
	if (KEY('S'))
		actor->translate(Vector2D(0, -100) * dt);

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
