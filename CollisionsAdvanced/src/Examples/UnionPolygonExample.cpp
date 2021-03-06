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
	mouse.set(ofGetMouseX(), ofGetHeight() - ofGetMouseY());
	oscilation += toRadians(30) * ofGetLastFrameTime();
}

void UnionPolygonExample::draw()
{
	auto variationX = sin(oscilation);

	//Axis Aligned Bounding Boxes Union
	auto boxA = AABB(AABB(Vector2D(variationX * 300.0f + 300, 500.0f), Vector2D(100, 150)));
	auto boxB = AABB(AABB(Vector2D(400.0f, variationX * 300.0f + 400.0f), Vector2D(100 + variationX * 100, 100.0f)));
	
	auto aabbDraw = make_shared<ofAABB_DrawHelper>();

	cg::setColor(Vector3D(255, 255, 255));
	boxA.draw(aabbDraw);
	boxB.draw(aabbDraw);

	cg::setColor(Vector3D(255, 255, 0));
	auto boxC = AABB::newByUnion(boxA, boxB);
	boxC.draw(aabbDraw);

	//Bounding Circles Union
	auto circleA = BoundingCircle(Vector2D(500.0f + 400 * variationX, 400.0f), 10);
	auto circleB = BoundingCircle(Vector2D(200.0f, 300.0f + 200.0f * variationX), 100 * variationX + 100);
	
	auto bcDraw = make_shared<ofBC_DrawHelper>();

	cg::setColor(Vector3D(255, 255, 255));
	circleA.draw(bcDraw);
	circleB.draw(bcDraw);
	
	auto circleC = BoundingCircle::newByUnion(circleA, circleB);

	cg::setColor(Vector3D(255, 255, 0));
	circleC.draw(bcDraw);

	//Drawing the line between circles to debug algorithm
	cg::setColor(Vector3D(0, 0, 255));
	auto offset = (circleB.position - circleA.position);
	auto v1 = -resize(circleA.position - circleB.position, circleB.radius);
	auto v2 = -resize(circleB.position - circleA.position, circleA.radius);
	//cg::drawLine(circleA.p + v2, circleA.p + offset + v1);
}

void UnionPolygonExample::close()
{
}

IScreen* UnionPolygonExample::nextScreen()
{
	return this;
}