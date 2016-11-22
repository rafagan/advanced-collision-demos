#pragma once

#include <ofImage.h>
#include "Math/Vector2D.h"
#include "Math/AABB.h"
#include "Math/BoundingCircle.h"

class Bitmask
{
	ofImage* image;
	math::AABB* broadPhaseBox;
	function<bool(ofVec4f)> isColorKey;

	static function<bool(ofVec4f)> defaultColorKey();
public:
	explicit Bitmask();
	explicit Bitmask(ofImage& image, math::AABB& broadPhaseBox, function<bool(ofVec4f)> isColorKey = nullptr);

	bool testCollision(const Bitmask& other) const;
	void transform(math::Vector2D _position, float angle, math::Vector2D _size, bool centered);

	void removeArea(math::AABB& region);
	void removeArea(math::BoundingCircle& region);

	virtual ~Bitmask();
};
