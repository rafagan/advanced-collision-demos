#include "UnionPolygonExample.h"
#include "DrawUtils.h"


UnionPolygonExample::UnionPolygonExample()
{
}


UnionPolygonExample::~UnionPolygonExample()
{
}

void UnionPolygonExample::init()
{
}

void UnionPolygonExample::update()
{
}

void UnionPolygonExample::draw()
{
	cg::drawBox(math::Vector2D(300, 300), math::Vector2D(300, 300));
}

void UnionPolygonExample::close()
{
}

IScreen* UnionPolygonExample::nextScreen()
{
	return this;
}
