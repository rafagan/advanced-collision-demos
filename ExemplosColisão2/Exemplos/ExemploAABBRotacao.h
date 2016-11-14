#pragma once

#include "../IScreen.h"
#include <c2d2/chien2d2.h>

class Actor;

class ExemploAABBRotacao : public IScreen {
private:
	C2D2_Mouse* mouse;
	C2D2_Botao* keys;
	Actor* actor;
public:
	explicit ExemploAABBRotacao();

	virtual void init();
	virtual void update(const float dt);
	virtual void draw();
	virtual void close();
	virtual IScreen* nextScreen();

	virtual ~ExemploAABBRotacao();
};

