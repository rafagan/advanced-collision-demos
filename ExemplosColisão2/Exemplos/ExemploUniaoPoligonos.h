#pragma once

#include "../IScreen.h"

class ExemploUniaoPoligonos : public IScreen {
public:
	explicit ExemploUniaoPoligonos();

	virtual void init();
	virtual void update(const float dt);
	virtual void draw();
	virtual void close();
	virtual IScreen* nextScreen();

	virtual ~ExemploUniaoPoligonos();
};

