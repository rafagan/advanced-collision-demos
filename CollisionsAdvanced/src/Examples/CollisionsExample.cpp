#include "CollisionsExample.h"
#include "../EventManager.h"
#include "../DrawUtils.h"
#include "../Math/ofDraw.h"

using namespace math;

math::Vector3D CollisionsExample::getElementColor(const ColliderWrapper& wrapper) {
	return wrapper.selected ? Vector3D(255, 255, 255) :(
		wrapper.contains ? Vector3D(125, 125, 125) :(
			wrapper.intersects ? Vector3D(0, 255, 0) : wrapper.defaultColor));
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

//TODO: Ugly code. Another better solution would be plan some kind of inheritance in AABB and BoundingBox to make polymorphism
void CollisionsExample::testIntersects(ColliderWrapper& wrapper)
{
	auto c1 = wrapper.boxOrCircle == 1 ?
		static_cast<AABB*>(wrapper.mathElement) :
		nullptr;
	auto c2 = wrapper.boxOrCircle == 2 ?
		static_cast<BoundingCircle*>(wrapper.mathElement) :
		nullptr;

	for (auto i = 0; i < wrappers.size(); i++) {
		auto tmp = &wrappers[i];
		if (tmp->id == wrapper.id) continue;

		if (tmp->boxOrCircle == 1) {
			auto elem = static_cast<AABB*>(tmp->mathElement);

			if ((c1 != nullptr && elem->contains(*c1)) || (c2 != nullptr && elem->contains(*c2))) {
				tmp->contains = true;
				return;
			}
			tmp->contains = false;

			if ((c1 != nullptr && elem->intersects(*c1)) || (c2 != nullptr && elem->intersects(*c2))) {
				wrapper.intersects = true;
				return;
			}
			wrapper.intersects = false;
		} else if (tmp->boxOrCircle == 2) {
			auto elem = static_cast<BoundingCircle*>(tmp->mathElement);

			if ((c1 != nullptr && elem->contains(*c1)) || (c2 != nullptr && elem->contains(*c2))) {
				tmp->contains = true;
				return;
			}
			tmp->contains = false;

			if ((c1 != nullptr && elem->intersects(*c1)) || (c2 != nullptr && elem->intersects(*c2))) {
				wrapper.intersects = true;
				return;
			}
			wrapper.intersects = false;
		}
	}
}

void CollisionsExample::testContains(ColliderWrapper& wrapper)
{

}

CollisionsExample::CollisionsExample(): currentSelected(nullptr) {
}

void CollisionsExample::init()
{
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

	if (KEY(OF_KEY_UP)) currentSelected->size += 60 * ofGetLastFrameTime();
	if (KEY(OF_KEY_DOWN)) currentSelected->size -= 60 * ofGetLastFrameTime();

	for (auto i = 0; i < wrappers.size(); i++) {
		auto tmp = &wrappers[i];
		testIntersects(*tmp);
		
		cg::setColor(getElementColor(*tmp));
		if (tmp->boxOrCircle == 1) {
			auto elem = static_cast<AABB*>(tmp->mathElement);
			elem->position = tmp->position;
			elem->size.set(tmp->size, tmp->size);
		} else if (tmp->boxOrCircle == 2) {
			auto elem = static_cast<BoundingCircle*>(tmp->mathElement);
			elem->position = tmp->position;
			elem->radius = tmp->size;
		}
	}
}

void CollisionsExample::draw()
{
	for(auto i = 0; i < wrappers.size(); i++) {
		auto tmp = &wrappers[i];
		if(tmp->selected) continue;
		drawElement(*tmp);
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