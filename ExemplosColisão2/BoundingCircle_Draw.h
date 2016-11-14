#pragma once

#include <c2d2/chien2d2primitivas.h>
#include "math/BoundingCircle.h"

class BoundingCircle_Draw : public math::BoundingCircle {
public:
	virtual void draw(math::Vector3D color) const
	{
		C2D2P_Circulo((int)position.x,(int)position.y,(int)radius,(unsigned char)color.x, (unsigned char)color.y, (unsigned char)color.z);
	}

	BoundingCircle_Draw() {}

	BoundingCircle_Draw(const BoundingCircle& other)
	{
		this->position = other.position;
		this->radius = other.radius;
	}
};