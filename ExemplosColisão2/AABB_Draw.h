#pragma once

#include <c2d2/chien2d2primitivas.h>
#include "math/AABB.h"

class AABB_Draw : public math::AABB
{
public:
	virtual void draw(math::Vector3D color) const
	{
		C2D2P_Retangulo((int)left(), (int)top(), (int)right(), (int)bottom(), (unsigned char)color.x, (unsigned char)color.y, (unsigned char)color.z);
	}

	AABB_Draw() {}

	AABB_Draw(const AABB& other)
	{
		this->position = other.position;
		this->size = other.size;
	}
};

