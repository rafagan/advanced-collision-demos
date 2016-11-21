#pragma once
#include "../IScreen.h"
#include "../Math/Vector2D.h"
#include "../Math/AABB.h"
#include "../Math/BoundingCircle.h"
#include "../Math/Vector3D.h"

struct ColliderWrapper {
	int boxOrCircle;
	math::Vector3D defaultColor;
	void* mathElement;
	short int id;

	bool selected = false;
	bool intersects = false;
	bool contains = false;
	float size;
	math::Vector2D position;
};

class CollisionsExample : public IScreen
{
	math::Vector2D mouse;
	std::array<ColliderWrapper, 4> wrappers;
	ColliderWrapper* currentSelected;

	math::AABB boxRed, boxBlue;
	math::BoundingCircle circleYellow, circleCyan;

	static math::Vector3D getElementColor(const ColliderWrapper& wrapper);
	void setSelected(int id);
	void drawElement(const ColliderWrapper& wrapper) const;
	void testCollision(ColliderWrapper& wrapper);
public:
	explicit CollisionsExample();
	void init() override;
	void update() override;
	void draw() override;
	void close() override;
	IScreen* nextScreen() override;
	virtual ~CollisionsExample();
};