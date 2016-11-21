#include "UnionPolygonExample.h"
#include "../Math/AABB.h"
#include "../Math/ofDraw.h"
#include "../Math/BoundingCircle.h"
#include "../DrawUtils.h"

using namespace math;

UnionPolygonExample::UnionPolygonExample(): oscilation(0) {
}


UnionPolygonExample::~UnionPolygonExample()
{
}

void UnionPolygonExample::init()
{
}

void UnionPolygonExample::update()
{
	mouse.set(ofGetMouseX(), ofGetMouseY());
	oscilation += toRadians(30) * ofGetLastFrameTime();
}

void UnionPolygonExample::draw()
{
	auto variationX = sin(oscilation);

	//Axis Aligned Bounding Boxes Union
	auto boxA = AABB(AABB(mouse, Vector2D(100, 150)));
	auto boxB = AABB(AABB(Vector2D(400, 200), Vector2D(100 + variationX * 100, 100.0f)));
	
	auto aabbDraw = make_shared<ofAABB_DrawHelper>();

	cg::setColor(Vector3D(255, 255, 255));
	boxA.draw(aabbDraw);
	boxB.draw(aabbDraw);

	cg::setColor(Vector3D(255, 255, 0));
	auto boxC = AABB::newByUnion(boxA, boxB);
	boxC.draw(aabbDraw);

	//Bounding Circles Union
	auto circleA = BoundingCircle(Vector2D(500 + variationX * 300, 100.0f), 10);
	auto circleB = BoundingCircle(Vector2D(700, 200), variationX * 50);
	
	auto bcDraw = make_shared<ofBC_DrawHelper>();

	cg::setColor(Vector3D(255, 255, 255));
	circleA.draw(bcDraw);
	circleB.draw(bcDraw);
	
	auto circleC = BoundingCircle::newByUnion(circleA, circleB);

	cg::setColor(Vector3D(255, 255, 0));
	circleC.draw(bcDraw);
}

void UnionPolygonExample::close()
{
}

IScreen* UnionPolygonExample::nextScreen()
{
	return this;
}