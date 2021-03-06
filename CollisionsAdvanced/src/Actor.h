#pragma once

#include "GameObject.h"

#include <vector>
#include <initializer_list>
#include "Math/MathIncluder.h"
#include <ofImage.h>
#include "Bitmask.h"

class Actor : public GameObject
{
	ofImage image;
	vector<unsigned int> frames;
	unsigned int frame;
	float framerate;
	long double timeSpent;
	bool centered;
	float angle;

	math::Vector2D size;
	math::Vector3D color;
	math::Vector2D position;
	math::Vector2D localScale;

	math::AABB box;
	Bitmask bitmask;

	void updateAnimationFrames();
public:
	explicit Actor(): frame(0), framerate(0), timeSpent(0), centered(false), angle(0) {}
	explicit Actor(float width, float height, std::initializer_list<unsigned int> frames, float framerate = 0);
	
	void init(const string fileName, function<bool(ofVec4f)> isColorKey = nullptr);

	math::Vector2D getSizeScaled() const;
	math::AABB getBox() const;

	void setPosition(float x, float y);
	void setPosition(math::Vector2D position);
	void setAngle(float angle);
	void setScale(math::Vector2D scale);
	void setColor(math::Vector3D color);

	virtual void translate(float x, float y);
	virtual void translate(math::Vector2D translation);
	virtual void rotate(float angle);
	virtual void scale(float ratio);
	virtual void scale(math::Vector2D ratio);

	virtual void update();

	virtual void draw() const;
	virtual void drawIntersection(const Actor& other) const;

	//Pixel Perfect Collision Check
	virtual bool testCollision(const Actor& other) const;

	virtual ~Actor(void);
};