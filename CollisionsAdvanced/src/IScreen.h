#pragma once

class IScreen {
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void close() = 0;
	virtual IScreen* nextScreen() = 0;

	virtual ~IScreen() {};
};