#include "ExemploUniaoPoligonos.h"
#include "../Math/MathIncluder.h"
#include "../AABB_Draw.h"
#include "../BoundingCircle_Draw.h"

using namespace math;

ExemploUniaoPoligonos::ExemploUniaoPoligonos()
{}


ExemploUniaoPoligonos::~ExemploUniaoPoligonos()
{}

void ExemploUniaoPoligonos::init()
{}

void ExemploUniaoPoligonos::update(const float dt)
{

}

void ExemploUniaoPoligonos::draw()
{
	//Testando união de bounding boxes
	AABB_Draw a(AABB(Vector2D(50, 100), Vector2D(100, 150))), b(AABB(Vector2D(200, 200), Vector2D(100, 100)));
	a.draw(Vector3D(255, 255, 0));
	b.draw(Vector3D(125, 125, 125));
	AABB_Draw c = AABB_Draw::newByUnion(a, b);
	c.draw(Vector3D(255, 255, 255));

	//Testando união de bounding circles
	BoundingCircle_Draw ca(BoundingCircle(Vector2D(500, 100), 10)), cb(BoundingCircle(Vector2D(700, 200), 10));
	ca.draw(Vector3D(255, 255, 0));
	cb.draw(Vector3D(125, 125, 125));
	BoundingCircle_Draw cc = BoundingCircle_Draw::newByUnion(ca, cb);
	cc.draw(Vector3D(255, 255, 255));
}

void ExemploUniaoPoligonos::close()
{

}

IScreen* ExemploUniaoPoligonos::nextScreen()
{
	return this;
}
