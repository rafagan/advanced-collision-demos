#include "AABB.h"

#include <cmath>
#include "BoundingCircle.h"
#include "AffineTransform.h"

using namespace math;
using namespace std;

AABB::AABB(float x, float y, float width, float height)
	:position(x, y), size(width, height)
{
}

AABB::AABB(Vector2D _position, Vector2D _size)
	: position(_position), size(_size)
{
}

AABB AABB::newByBounds(float left, float right, float top, float bottom)
{
	return AABB(left, top, right - left, bottom - top);
}

AABB AABB::newByUnion(const AABB& a, const AABB& b)
{
	AABB boxUnion = AABB(
		Vector2D(a.left() < b.left() ? a.left() : b.left(), a.top() < b.top() ? a.top() : b.top()),
		Vector2D(a.right() > b.right() ? a.right() : b.right(), a.bottom() > b.bottom() ? a.bottom() : b.bottom())
	);
	boxUnion.size -= a.position;

	return boxUnion;
}

bool AABB::contains(const Vector2D& point) const
{
	bool left = (point.x >= position.x);
	bool right = (point.x <= (position.x + size.x));
	bool top = (point.y >= position.y);
	bool bottom = (point.y <= (position.y + size.y));

	return (left && right && top && bottom);
}

bool AABB::contains(const AABB& other) const
{
	auto p = other.getBounds();
	return contains(p[0]) && contains(p[1]) && contains(p[2]) && contains(p[3]);
}

bool AABB::contains(const BoundingCircle& circle) const
{
	//Box externa ao circulo
	Vector2D halfSize(circle.radius, circle.radius);
	AABB outerBox(circle.position - halfSize, halfSize * 2);

	return contains(outerBox);
}

bool AABB::intersects(const AABB& other) const
{
	if(left() > other.right())
		return false;
	if(right() < other.left())
		return false;
	if(top() > other.bottom())
		return false;
	if(bottom() < other.top())
		return false;

	return true;
}

AABB AABB::intersection(const AABB& other) const
{
	AABB intersectionBox;
	intersectionBox.position.x = (float)(left() > other.left() ? left() : other.left());
	intersectionBox.position.y = (float)(top() > other.top() ? top() : other.top());
	intersectionBox.size.x = (float)(right() < other.right() ? right() : other.right());
	intersectionBox.size.y = (float)(bottom() < other.bottom() ? bottom() : other.bottom());

	intersectionBox.size -= intersectionBox.position;

	return intersectionBox;
}

bool AABB::intersects(const BoundingCircle& circle) const
{
	Vector2D nearestPoint;

	if(circle.position.x < left())
		nearestPoint.x = left();
	else if(circle.position.x > right())
		nearestPoint.x = right();
	else
		nearestPoint.x = circle.position.x;

	if(circle.position.y < top())
		nearestPoint.y = top();
	else if(circle.position.y > bottom())
		nearestPoint.y = bottom();
	else
		nearestPoint.y = circle.position.y;

	return distanceSqr(nearestPoint, circle.position) < powf(circle.radius, 2);
}

void AABB::transform(Vector2D _position, float angle, Vector2D _size, bool centered)
{
	array<math::Vector2D, 4> bounds;

	if(centered) {
		Vector2D extents = _size / 2;
		bounds[0] = Vector2D(-extents);
		bounds[1] = Vector2D(extents.x, -extents.y);
		bounds[2] = Vector2D(extents);
		bounds[3] = Vector2D(-extents.x, extents.y);
	} else {
		bounds[0] = Vector2D(0, 0);
		bounds[1] = Vector2D(_size.x, 0);
		bounds[2] = Vector2D(_size.x, _size.y);
		bounds[3] = Vector2D(0, _size.y);
	}

	Matrix3 world = rh::newAffineRotation(angle);
	for(int i = 0; i < 4; ++i)
		bounds[i] = rh::transform(world, bounds[i]);

	Vector2D p = Vector2D(
		min({bounds[0].x, bounds[1].x, bounds[2].x, bounds[3].x}),
		min({bounds[0].y, bounds[1].y, bounds[2].y, bounds[3].y}));
	Vector2D s = Vector2D(
		max({bounds[0].x, bounds[1].x, bounds[2].x, bounds[3].x}),
		max({bounds[0].y, bounds[1].y, bounds[2].y, bounds[3].y}));

	position = _position + p;
	size = s - p;
}

float AABB::left() const
{
	return position.x;
}

float AABB::right() const
{
	return (position.x + size.x);
}

float AABB::top() const
{
	return position.y;
}

float AABB::bottom() const
{
	return (position.y + size.y);
}

//Também chamado de extents por algumas engines
math::Vector2D AABB::getCenter() const
{
	return position + size / 2;
}

array<math::Vector2D, 4> AABB::getBounds() const
{
	array<math::Vector2D, 4> a;
	a[0] = Vector2D(left(), top());
	a[1] = Vector2D(right(), top());
	a[2] = Vector2D(right(), bottom());
	a[3] = Vector2D(left(), bottom());

	return a;
}

ostream& math::operator<<(ostream& output, const AABB& box)
{
	output << "Position: " << box.position << "\nSize: " << box.size;
	return output;	
}

AABB::~AABB(void)
{
}