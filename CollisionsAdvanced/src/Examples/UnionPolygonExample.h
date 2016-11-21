#pragma once
#include "../IScreen.h"
class UnionPolygonExample : public IScreen
{
public:
	explicit UnionPolygonExample();
	virtual ~UnionPolygonExample();

	void init() override;
	void update() override;
	void draw() override;
	void close() override;
	IScreen* nextScreen() override;
};