#include "BoundingCircle.h"

#include "AABB.h"
#include <cmath>

using namespace math;

BoundingCircle::BoundingCircle(void)
{
}

BoundingCircle::BoundingCircle(float x, float y, float _radius)
	:position(x, y), radius(_radius)
{}

BoundingCircle::BoundingCircle(math::Vector2D _position, float _radius)
	: position(_position), radius(_radius)
{}

BoundingCircle BoundingCircle::newByUnion(const BoundingCircle& a, const BoundingCircle& b)
{
	Vector2D offset = a.position - b.position;
	return BoundingCircle(offset/2 + b.position,(offset.size() + a.radius + b.radius)/2);
}

bool BoundingCircle::contains(const Vector2D& point) const
{
	return distanceSqr(position, point) < position.sizeSqr();
}

bool BoundingCircle::contains(const AABB& box) const
{
	//Box interna ao círculo
	float apothem = radius * sqrtf(2) / 2;
	Vector2D innerBoxCenter(apothem, apothem);
	AABB innerBox(position - innerBoxCenter, innerBoxCenter * 2);

	return innerBox.contains(box);
}

bool BoundingCircle::contains(const BoundingCircle& other) const
{
	return distanceSqr(position, other.position) < powf(radius - other.radius, 2);
}

bool BoundingCircle::intersects(const AABB& box) const
{
	return box.intersects(*this);
}

bool BoundingCircle::intersects(const BoundingCircle& other) const
{
	return distanceSqr(position, other.position) < powf(radius + other.radius, 2);
}

std::ostream& math::operator<<(std::ostream& output, const BoundingCircle& circle)
{
	output << "Position: " << circle.position << "\nRadius: " << circle.radius;
	return output;
}

BoundingCircle::~BoundingCircle(void)
{
}