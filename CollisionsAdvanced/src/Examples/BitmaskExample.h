#pragma once
#include "IScreen.h"

class BitmaskExample : public IScreen
{
public:
	explicit BitmaskExample();
	virtual ~BitmaskExample();

	void init() override;
	void update() override;
	void draw() override;
	void close() override;
	IScreen* nextScreen() override;
};