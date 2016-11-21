#pragma once

#include "../IScreen.h"
#include "../Actor.h"

class AABBRotationExample : public IScreen
{
	Actor* actor;
public:
	explicit AABBRotationExample();
	virtual ~AABBRotationExample();

	void init() override;
	void update() override;
	void draw() override;
	void close() override;
	IScreen* nextScreen() override;
};
