#include "UnionPolygonExample.h"
#include "../Math/AABB.h"
#include "../Math/ofDraw.h"
#include "../Math/BoundingCircle.h"

using namespace math;

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
	//Axis Aligned Bounding Boxes Union
	auto boxA = AABB(AABB(Vector2D(50, 100), Vector2D(100, 150)));
	auto boxB = AABB(AABB(Vector2D(200, 200), Vector2D(100, 100)));
	
	boxA.draw(make_shared<ofAABB_DrawHelper>());
	boxB.draw(make_shared<ofAABB_DrawHelper>());
	
	auto boxC = AABB::newByUnion(boxA, boxB);
	boxC.draw(make_shared<ofAABB_DrawHelper>());

	//Bounding Circles Union
	auto circleA = BoundingCircle(Vector2D(500, 100), 10);
	auto circleB = BoundingCircle(Vector2D(700, 200), 10);
	
	circleA.draw(Vector3D(255, 255, 0));
	circleB.draw(Vector3D(125, 125, 125));
	
	auto circleC = BoundingCircle::newByUnion(circleA, circleB);
	circleC.draw(Vector3D(255, 255, 255));
}

void UnionPolygonExample::close()
{
}

IScreen* UnionPolygonExample::nextScreen()
{
	return this;
}