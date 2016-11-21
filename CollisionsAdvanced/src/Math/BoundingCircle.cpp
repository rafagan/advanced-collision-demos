/******************************************************************************
*
* COPYRIGHT Ráfagan S. de Abreu. ALL RIGHTS RESERVED.
*
* This software can be copied, stored and distributed without
* author's prior authorization. Just let him know and leave this header in this source code.
*
* This file was made available on https://github.com/rafagan/advanced-collision-demos and it is free
* to be restributed or used under Apache 2.0 license:
* http://www.apache.org/licenses/LICENSE-2.0/
*
******************************************************************************/

#include "BoundingCircle.h"

#include <cmath>
#include "AABB.h"

using namespace math;

BoundingCircle::BoundingCircle(void): radius(0) {
}

BoundingCircle::BoundingCircle(float x, float y, float _radius)
	:position(x, y), radius(_radius)
{}

BoundingCircle::BoundingCircle(math::Vector2D _position, float _radius)
	: position(_position), radius(_radius)
{}

//ok
BoundingCircle BoundingCircle::newByUnion(const BoundingCircle& a, const BoundingCircle& b)
{
	auto offset = (b.position - a.position);
	auto v1 = -resize(a.position - b.position, b.radius);
	auto v2 = -resize(b.position - a.position, a.radius);

	return BoundingCircle(a.p + (v1 + v2 + offset) / 2, a.radius + (v1 + v2 + offset).size() / 2);
}

BoundingCircle BoundingCircle::innerCircleFromBox(const AABB& box)
{
	if (box.size.x != box.size.y)
		return BoundingCircle();
	return BoundingCircle(box.position + box.size / 2, box.size.x / 2);
}

BoundingCircle BoundingCircle::outerCircleFromBox(const AABB& box)
{
	if (box.size.x != box.size.y)
		return BoundingCircle();
	return BoundingCircle(box.position + box.size / 2, (box.size / 2).size());
}

float BoundingCircle::innerBoxApothem(const BoundingCircle& circle)
{
	return circle.innerBoxApothem();
}

//ok
bool BoundingCircle::contains(const Vector2D& point) const
{
	return distanceSqr(position, point) < pow(radius, 2);
}

//TODO arrumar
bool BoundingCircle::contains(const AABB& box) const
{
	return false;
}

//ok
bool BoundingCircle::contains(const BoundingCircle& other) const
{
	//https://goo.gl/VFI2w5
	return distanceSqr(position, other.position) < powf(radius - other.radius, 2);
}

//ok
bool BoundingCircle::intersects(const AABB& box) const
{
	return box.intersects(*this);
}

//ok
bool BoundingCircle::intersects(const BoundingCircle& other) const
{
	return distanceSqr(position, other.position) < powf(radius + other.radius, 2);
}

//https://goo.gl/dJ9EBF
float BoundingCircle::innerBoxApothem() const
{
	return radius * sqrtf(2) / 2;
}

void BoundingCircle::draw(std::shared_ptr<IBoundingCircleDrawHelper> helper) const
{
	helper->draw(*this);
}

std::ostream& math::operator<<(std::ostream& output, const BoundingCircle& circle)
{
	output << "Position: " << circle.position << "\nRadius: " << circle.radius;
	return output;
}

BoundingCircle::~BoundingCircle(void)
{
}