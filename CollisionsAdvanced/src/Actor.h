#pragma once

#include "GameObject.h"

#include <vector>
#include <initializer_list>
#include "Math/MathIncluder.h"
#include <ofImage.h>

//#include "AABB_Draw.h"

class Actor : public GameObject
{
	ofImage image;
	std::vector<unsigned int> frames;
	unsigned int frame;
	float framerate;
	long double timeSpent;
	bool centered;
	float angle;

	math::Vector2D size;
	math::Vector3D color;
	math::Vector2D position;
	math::Vector2D localScale;

public:
	explicit Actor(): frame(0), framerate(0), timeSpent(0), centered(false), angle(0) {}
	explicit Actor(const std::string fileName, float width, float height, std::initializer_list<unsigned int> frames, float framerate = 0);
	
	void setPosition(float x, float y);
	void setPosition(math::Vector2D position);
	void setAngle(float angle);
	void setScale(math::Vector2D scale);
	void setColor(math::Vector3D color);

	virtual void draw(unsigned char alpha = 255) const;
	//virtual void drawIntersection(const Actor& other) const;
	virtual void update();

	virtual ~Actor(void);
};