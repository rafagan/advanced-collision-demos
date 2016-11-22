#pragma once

#include <ofImage.h>
#include "Math/Vector2D.h"
#include "Math/AABB.h"
#include "Math/BoundingCircle.h"

class Bitmask
{
	ofImage* image;
	math::AABB* broadPhaseBox;
	math::Vector2D* dimensions;
	vector<unsigned int>* frames;
	unsigned int* frame;
	function<bool(ofVec4f)> isColorKey;

	static function<bool(ofVec4f)> defaultColorKey();
	ofVec4f pixelColor(int x, int y) const;
public:
	explicit Bitmask();
	explicit Bitmask(
		ofImage& image, 
		math::AABB& broadPhaseBox, 
		math::Vector2D* dimensions = nullptr, 
		vector<unsigned int>* frames = nullptr, 
		unsigned int* frame = nullptr, 
		function<bool(ofVec4f)> isColorKey = nullptr);

	bool testCollision(const Bitmask& other) const;
	void transform(math::Vector2D position, float angle, math::Vector2D size, bool centered);

	void removeArea(math::AABB& region);
	void removeArea(math::BoundingCircle& region);

	virtual ~Bitmask();
};
