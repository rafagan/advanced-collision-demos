#pragma once
#include "../IScreen.h"
#include "../Math/Vector2D.h"

class UnionPolygonExample : public IScreen
{
	float oscilation;
	math::Vector2D mouse;
public:
	explicit UnionPolygonExample();
	virtual ~UnionPolygonExample();

	void init() override;
	void update() override;
	void draw() override;
	void close() override;
	IScreen* nextScreen() override;
};
