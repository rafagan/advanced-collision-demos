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

//Testando
bool BoundingCircle::contains(const Vector2D& point) const
{
	return distanceSqr(position, point) < (position - point).sizeSqr();
}

//Testando
bool BoundingCircle::contains(const AABB& box) const
{
	//Box inside the circle
	//https://goo.gl/Yy2rpk
	auto apothem = radius * sqrtf(2) / 2;
	Vector2D innerBoxCenter(apothem, apothem);
	AABB innerBox(position - innerBoxCenter, innerBoxCenter * 2);

	return innerBox.contains(box);
}

//ok
bool BoundingCircle::contains(const BoundingCircle& other) const
{
	return contains(other.position);
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