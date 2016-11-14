#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Vector3D.h"

namespace math {
	class AABB;

	class BoundingCircle {
		public:

		static BoundingCircle newByUnion(const BoundingCircle& a, const BoundingCircle& b);

		math::Vector2D position;
		float radius;

		explicit BoundingCircle(void);
		explicit BoundingCircle(float x, float y, float radius);
		explicit BoundingCircle(math::Vector2D position, float radius);

		bool contains(const Vector2D& point) const;
		bool contains(const AABB& box) const;
		bool contains(const BoundingCircle& other) const;

		bool intersects(const AABB& box) const;
		bool intersects(const BoundingCircle& other) const;

		virtual void draw(math::Vector3D color) const {};

		virtual ~BoundingCircle(void);
	};

	std::ostream& operator<<(std::ostream& output, const BoundingCircle&);
}