#pragma once

#include "../IScreen.h"
#include "../Actor.h"

class ExemploBitmask : public IScreen {
private:
	C2D2_Mouse* mouse;
	C2D2_Botao* keys;
	Actor *actor1, *actor2;
public:
	explicit ExemploBitmask();

	virtual void init();
	virtual void update(const float dt);
	virtual void draw();
	virtual void close();
	virtual IScreen* nextScreen();

	virtual ~ExemploBitmask();
};

