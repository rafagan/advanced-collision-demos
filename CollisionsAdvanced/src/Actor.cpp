#include "Actor.h"

#include "DrawUtils.h"
#include "Math/ofDraw.h"

using namespace std;
using namespace math;

void Actor::updateAnimationFrames()
{
	if (frames.size() > 1)
		if (ofGetElapsedTimef() > timeSpent + framerate) {
			timeSpent = ofGetElapsedTimef();
			frame = frame + 1 == frames.size() ? 0 : ++frame;
		}
		else
			frame = 0;
}

Actor::Actor(const std::string fileName, float _width, float _height, std::initializer_list<unsigned> _frames, float _framerate)
	: frames(_frames), frame(0), framerate(_framerate), timeSpent(0), centered(true), color(Vector3D(255, 255, 255))
{
	image.load(fileName);
	size = Vector2D(
		_width > 0 ? _width : image.getWidth(), 
		_height > 0 ? _height : image.getHeight());

	box.size = getSizeScaled();

	if (frames.empty()) 
		frames.push_back(0);
	frames.resize(frames.size());

	setAngle(0.0f);
	setPosition(Vector2D());
	setScale(Vector2D(1, 1));
}

Vector2D Actor::getSizeScaled() const
{
	return Vector2D(localScale.x * size.x, localScale.y * size.y);
}

math::AABB Actor::getBox() const
{
	return box;
}

void Actor::setPosition(float x, float y)
{
	this->position.set(x, y);
}

void Actor::setPosition(Vector2D position)
{
	this->position = position;
}

void Actor::setAngle(float angle)
{
	this->angle = angle;
}

void Actor::setScale(math::Vector2D scale)
{
	this->localScale.set(scale);
}

void Actor::setColor(Vector3D color)
{
	this->color = color;
}

void Actor::translate(float x, float y)
{
	translate(Vector2D(x, y));
}

void Actor::translate(Vector2D translation)
{
	setPosition(position + translation);
}

void Actor::rotate(float angle)
{
	setAngle(this->angle + angle);
}

void Actor::scale(float ratio)
{
	setScale(localScale + localScale * ratio);
}

void Actor::scale(Vector2D ratio)
{
	setScale(Vector2D(localScale.x * ratio.x, localScale.y * ratio.y));
}

void Actor::update()
{
	//Update animation
	updateAnimationFrames();

	//position.y += 10 * ofGetLastFrameTime();
	box.transform(position, angle, getSizeScaled(), centered);

	//Uncomment for an automatic AABB rotation example
	rotate(toRadians(30 * ofGetLastFrameTime()));
}

void Actor::draw() const
{
	auto world = 
		lh::newAffineScale(localScale.x, localScale.y) * 
		lh::newAffineRotation(angle) * 
		lh::newAffineTranslation(position);

	cg::setColor(Vector3D(255, 255, 0));
	lh::draw(lh::flipY(world), image, size, frame);
	cg::setColor(Vector3D(255, 0, 0));
	box.draw(make_shared<ofAABB_DrawHelper>());
}

void Actor::drawIntersection(const Actor& other) const
{
	if (!box.intersects(other.box)) return;
	auto iBox = box.intersection(other.box);
	iBox.draw(make_shared<ofAABB_DrawHelper>());
}

bool Actor::testCollision(const Actor& other) const
{
	//Broad Phase
	if (!box.intersects(other.box)) return false;
	return true;
	
	//Narrow Phase
	//return testBitmaskCollision(other, box.intersection(other.box));
}

Actor::~Actor(void)
{	
}
