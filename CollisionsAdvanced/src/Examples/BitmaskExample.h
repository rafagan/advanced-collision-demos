#pragma once
#include "../IScreen.h"
#include "../Actor.h"

class BitmaskExample : public IScreen
{
	Actor actor1, actor2;
public:
	explicit BitmaskExample();
	virtual ~BitmaskExample();

	void init() override;
	void update() override;
	void draw() override;
	void close() override;
	IScreen* nextScreen() override;
};
