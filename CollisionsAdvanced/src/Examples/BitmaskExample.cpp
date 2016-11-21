#include "BitmaskExample.h"
#include "../DrawUtils.h"


BitmaskExample::BitmaskExample()
{
}


BitmaskExample::~BitmaskExample()
{
}

void BitmaskExample::init()
{
}

void BitmaskExample::update()
{
}

void BitmaskExample::draw()
{
	cg::drawBox(math::Vector2D(300, 300), math::Vector2D(300, 300));
}

void BitmaskExample::close()
{
}

IScreen* BitmaskExample::nextScreen()
{
	return this;
}
