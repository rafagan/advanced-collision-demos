#include "Actor.h"

#include "DrawUtils.h"
#include "Math/ofDraw.h"

using namespace std;
using namespace math;

Actor::Actor(const std::string fileName, float _width, float _height, std::initializer_list<unsigned> _frames, float _framerate)
	: frames(_frames), frame(0), framerate(_framerate), timeSpent(0), centered(true), color(Vector3D(255, 255, 255))
{
	image.load(fileName);
	size = Vector2D(
		_width > 0 ? _width : image.getWidth(), 
		_height > 0 ? _height : image.getHeight());

	//TODO: box.size = getSize();

	if (frames.empty()) 
		frames.push_back(0);
	frames.resize(frames.size());

	setAngle(0.0f);
	setPosition(Vector2D());
	setScale(Vector2D(1, 1));
}

void Actor::setPosition(float x, float y)
{
	this->position.set(x, y);
}

void Actor::setPosition(math::Vector2D position)
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

void Actor::setColor(math::Vector3D color)
{
	this->color = color;
}

void Actor::draw(unsigned char alpha) const
{
	auto world = 
		lh::newAffineScale(localScale.x, localScale.y) * 
		lh::newAffineRotation(angle) * 
		lh::newAffineTranslation(position);

	lh::draw(world, image);
	//TODO: box.draw(Vector3D(255,0,0));
}

void Actor::update()
{
	angle += 1 * ofGetLastFrameTime();
}

Actor::~Actor(void)
{	
}
