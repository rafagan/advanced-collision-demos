/******************************************************************************
*
* COPYRIGHT Ráfagan S. de Abreu. ALL RIGHTS RESERVED.
*
* This software can be copied, stored and distributed without
* author's prior authorization. Just let him know and leave this header in this source code.
*
* This file was made available on https://github.com/rafagan/basic-2D-collision-demos/ and it is free
* to be restributed or used under Apache 2.0 license:
* http://www.apache.org/licenses/
*
******************************************************************************/

#pragma once

#include "Vector2D.h"

namespace math {
	struct BoundingBox {
		BoundingBox() {};
		BoundingBox(math::Vector2D position, math::Vector2D size) 
			: position(position), size(size) {};
		BoundingBox(float x, float y, float width, float height)
			: position(x, y), size(width, height) {};
		BoundingBox(float left, float right, float top, float bottom, bool flipY = true)
			: position(left, top), size(right - left, flipY ? top - bottom : bottom - top) {};

		union
		{
			float xy[2];
			math::Vector2D position;
		};
		union
		{
			float wh[2];
			math::Vector2D size;
		};

		float left() const { return xy[0]; };
		float right() const { return xy[0] + wh[0]; };
		float bottom() const { return xy[1]; };
		float top() const { return xy[1] + wh[1]; };
	};

	typedef Vector2D Point;

	struct BoundingCircle {
		BoundingCircle() : radius(0.0f) {};
		BoundingCircle(math::Vector2D position, float radius) 
			: position(position), radius(radius) {};
		BoundingCircle(float x, float y, float radius) : position(x, y), radius(radius) {};

		union
		{
			float xy[2];
			math::Vector2D position;
		};
		float radius;
	};

	bool pointBoxCollisionCheck(const Point *point, const BoundingBox *box);

	//Three different ways to do the same thing (study case)
	bool AABBCollisionCheck(const BoundingBox *box, const BoundingBox *other);
	bool AABBInnerCollisionCheck(const BoundingBox *box, const BoundingBox *other);
	bool AABBOffsetCollisionCheck(const BoundingBox *box, const BoundingBox *other);

	bool circleCollisionCheck(const BoundingCircle *c1, const BoundingCircle *c2);
	bool circleBoxCollisionCheck(const BoundingBox *b, const BoundingCircle *c);
}