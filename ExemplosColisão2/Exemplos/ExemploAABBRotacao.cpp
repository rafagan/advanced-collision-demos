#include "ExemploAABBRotacao.h"

#include "../Math/MathIncluder.h"
#include "../Actor.h"

using namespace math;

ExemploAABBRotacao::ExemploAABBRotacao()
{}


ExemploAABBRotacao::~ExemploAABBRotacao()
{}

void ExemploAABBRotacao::init()
{
	keys = C2D2_PegaTeclas();
	mouse = C2D2_PegaMouse();

	actor = new Actor("quad.png", 0, 0, {});
	actor->setPosition(Vector2D(600, 400));
}

void ExemploAABBRotacao::update(const float dt)
{
	if(keys[C2D2_DIREITA].ativo) {
		actor->rotate(toRadians(30 * dt));
	}
	if(keys[C2D2_ESQUERDA].ativo) {
		actor->rotate(-toRadians(30 * dt));
	}
	if(keys[C2D2_CIMA].ativo) {
		actor->scale(0.01f);
	}
	if(keys[C2D2_BAIXO].ativo) {
		actor->scale(-0.01f);
	}
	if(keys[C2D2_A].ativo) {
		actor->translate(Vector2D(-100, 0) * dt);
	}
	if(keys[C2D2_D].ativo) {
		actor->translate(Vector2D(100, 0) * dt);
	}
	if(keys[C2D2_W].ativo) {
		actor->translate(Vector2D(0, -100) * dt);
	}
	if(keys[C2D2_S].ativo) {
		actor->translate(Vector2D(0, 100) * dt);
	}

	actor->update(dt);
}

void ExemploAABBRotacao::draw()
{
	actor->draw();
}

void ExemploAABBRotacao::close()
{

}

IScreen* ExemploAABBRotacao::nextScreen()
{
	return this;
}
