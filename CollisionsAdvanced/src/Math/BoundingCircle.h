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

#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Vector3D.h"

namespace math {
	class AABB;

	class BoundingCircle {
		public:

		static BoundingCircle newByUnion(const BoundingCircle& a, const BoundingCircle& b);

		Vector2D position;
		float radius;

		explicit BoundingCircle(void);
		explicit BoundingCircle(float x, float y, float radius);
		explicit BoundingCircle(Vector2D position, float radius);

		bool contains(const Vector2D& point) const;
		bool contains(const AABB& box) const;
		bool contains(const BoundingCircle& other) const;

		bool intersects(const AABB& box) const;
		bool intersects(const BoundingCircle& other) const;

		virtual void draw(Vector3D color) const {};

		virtual ~BoundingCircle(void);
	};

	std::ostream& operator<<(std::ostream& output, const BoundingCircle&);
}