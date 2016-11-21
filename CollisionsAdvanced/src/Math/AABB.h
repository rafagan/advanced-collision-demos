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

#include <array>
#include "Vector2D.h"
#include <memory>

namespace math {
	class AABB;
	class BoundingCircle;

	class IAABB_DrawHelper {
	public:
		virtual void draw(const AABB& box, bool invertY = true) const = 0;
		virtual ~IAABB_DrawHelper() {};
	};

	class AABB {
	public:
		static AABB newByBounds(float left, float right, float top, float bottom);
		static AABB newByUnion(const AABB& a, const AABB& b);

		/*
		This approach considers that position, size, angle, and scale values should be in the AABB
		The advantage is that we will have cleaner methods and the object of the class can be a reference to these attributes of the object
		The disadvantage is that they should always be updated, which generates duplicate data in classes
		A class whose drawing function is performed in the center of the image and not in the upper left 
		  corner can generate inconsistency in the application of the collision if the same position is used
		Another way to solve the problem would be receive data such as position and size as an argument of the methods
		*/
		union {
			Vector2D position;
			Vector2D p;
			float xy[2];
		};
		union {
			Vector2D size;
			Vector2D s;
			float wh[2];
		};

		explicit AABB() {};
		explicit AABB(float x, float y, float width, float height);
		explicit AABB(Vector2D position, Vector2D size);
		
		bool contains(const Vector2D& point) const;
		bool contains(const AABB& other) const;
		bool contains(const BoundingCircle& circle) const;

		bool intersects(const AABB& other) const;
		AABB intersection(const AABB& other) const;
		bool intersects(const BoundingCircle& circle) const;

		void transform(Vector2D position, float angle, Vector2D size, bool centered);

		float left() const;
		float right() const;
		float top(bool invertY = true) const;
		float bottom(bool invertY = true) const;

		Vector2D getCenter() const;
		std::array<Vector2D, 4> getBounds() const;

		void draw(std::shared_ptr<IAABB_DrawHelper> helper) const;

		virtual ~AABB(void);
	};

	std::ostream& operator<<(std::ostream& output, const AABB&);
}
