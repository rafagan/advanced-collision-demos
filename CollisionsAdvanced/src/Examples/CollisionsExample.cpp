#include "CollisionsExample.h"
#include "../EventManager.h"
#include "../DrawUtils.h"
#include "../Math/ofDraw.h"

using namespace math;

math::Vector3D CollisionsExample::getElementColor(const ColliderWrapper& wrapper) {
	return wrapper.colliding ? Vector3D(0, 255, 0) :
		wrapper.selected ? Vector3D(255, 255, 255) :
		wrapper.defaultColor;
}

void CollisionsExample::setSelected(int id) {
	for (auto i = 0; i < wrappers.size(); i++) {
		wrappers[i].selected = wrappers[i].id == id;
		if (wrappers[i].selected) currentSelected = &wrappers[i];
	}
}

void CollisionsExample::drawElement(const ColliderWrapper& tmp) const
{
	auto aabbDraw = make_shared<ofAABB_DrawHelper>();
	auto bcDraw = make_shared<ofBC_DrawHelper>();

	cg::setColor(getElementColor(tmp));
	if (tmp.boxOrCircle == 1) {
		auto elem = static_cast<AABB*>(tmp.mathElement);
		elem->draw(aabbDraw);
		cg::drawBox(elem->p + elem->s / 2, elem->s);
	}
	else if (tmp.boxOrCircle == 2) {
		auto elem = static_cast<BoundingCircle*>(tmp.mathElement);
		elem->draw(bcDraw);
		cg::drawCircle(elem->p, elem->radius);
	}
}

CollisionsExample::CollisionsExample() {
}

void CollisionsExample::init()
{
	
	boxBlue.position.set(600, 500);
	circleYellow.position.set(200, 500);
	circleCyan.position.set(600, 200);

	
	boxBlue.size.set(100, 100);
	circleYellow.radius = 80;
	circleCyan.radius = 80;

	wrappers[0].mathElement = &boxRed;
	wrappers[0].id = 0;
	wrappers[0].defaultColor = Vector3D(255, 0, 0);
	wrappers[0].boxOrCircle = 1;
	wrappers[0].position.set(200, 200);
	wrappers[0].size = 100;
	boxRed.position.set(wrappers[0].position);
	boxRed.size.set(wrappers[0].size, wrappers[0].size);

	wrappers[1].mathElement = &boxBlue;
	wrappers[1].id = 1;
	wrappers[1].defaultColor = Vector3D(0, 0, 255);
	wrappers[1].boxOrCircle = 1;
	wrappers[1].position.set(600, 500);
	wrappers[1].size = 100;
	boxBlue.position.set(wrappers[1].position);
	boxBlue.size.set(wrappers[1].size, wrappers[1].size);

	wrappers[2].mathElement = &circleYellow;
	wrappers[2].id = 2;
	wrappers[2].defaultColor = Vector3D(255, 255, 0);
	wrappers[2].boxOrCircle = 2;
	wrappers[2].position.set(200, 500);
	wrappers[2].size = 80;
	circleYellow.position.set(wrappers[2].position);
	circleYellow.radius = wrappers[2].size;

	wrappers[3].mathElement = &circleCyan;
	wrappers[3].id = 3;
	wrappers[3].defaultColor = Vector3D(0, 255, 255);
	wrappers[3].boxOrCircle = 2;
	wrappers[3].position.set(600, 200);
	wrappers[3].size = 80;
	circleCyan.position.set(wrappers[3].position);
	circleCyan.radius = wrappers[3].size;

	currentSelected = &wrappers[0];
}

void CollisionsExample::update()
{
	mouse = Vector2D(ofGetMouseX(), ofGetHeight() - ofGetMouseY()) 
		- (currentSelected->boxOrCircle == 1 ? Vector2D(currentSelected->size, currentSelected->size) / 2 : Vector2D());
	setSelected(EventManager::getLastKeyPressed() - '0' - 1);

	currentSelected->selected = true; //Workaround for the first selection (without input)
	currentSelected->position = mouse;

	if (KEY(OF_KEY_UP)) currentSelected->size++;
	if (KEY(OF_KEY_DOWN)) currentSelected->size--;

	for (auto i = 0; i < wrappers.size(); i++) {
		auto tmp = wrappers[i];
		cg::setColor(getElementColor(tmp));
		if (tmp.boxOrCircle == 1) {
			auto elem = static_cast<AABB*>(tmp.mathElement);
			elem->position = tmp.position;
			elem->size.set(tmp.size, tmp.size);

			//Testar colisão
		}
		else if (tmp.boxOrCircle == 2) {
			auto elem = static_cast<BoundingCircle*>(tmp.mathElement);
			elem->position = tmp.position;
			elem->radius = tmp.size;

			//Testar colisão
		}
	}
}

void CollisionsExample::draw()
{
	for(auto i = 0; i < wrappers.size(); i++) {
		auto tmp = wrappers[i];
		if(tmp.selected) continue;
		drawElement(tmp);
	}
	drawElement(*currentSelected);
}

void CollisionsExample::close()
{
}

IScreen* CollisionsExample::nextScreen()
{
	return this;
}

CollisionsExample::~CollisionsExample()
{
}
