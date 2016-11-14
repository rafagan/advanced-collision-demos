#pragma once

#include "GameObject.h"

#include <vector>
#include <initializer_list>
#include <c2d2/chien2d2.h>
#include "Math/MathIncluder.h"
#include "AABB_Draw.h"

class Actor : public GameObject
{
private:
	//Sprite
	unsigned int id;
	const C2D2_SpriteSet* c2d2_sprite;
	std::vector<unsigned int> frames;
	unsigned int frame;
	math::Vector2D size;
	math::Vector3D color;
	float framerate;
	long double timeSpent;
	bool centered;

	//Sistema de Coordenadas
	math::Matrix3 world;
	math::Vector2D position;
	float angle;
	math::Vector2D myScale;

	//Colisão
	AABB_Draw box;

	bool testBitmaskCollision(const Actor& other, math::AABB& intersectionBox) const;
	void fillSpriteIndexRowAndColumn(unsigned int row_col[2], const Actor& actor) const;
	SDL_Surface* getImage() const;
	bool isColorKey(Uint32 r, Uint32 g, Uint32 b, Uint32 a) const;
	bool testBitmaskColorKey(SDL_Surface* image,unsigned int x, unsigned int y) const;
public:
	explicit Actor() {};
	explicit Actor(const char* fileName, int width, int height, std::initializer_list<unsigned int> frames, float framerate = 0);

	virtual void update(float dt);
	virtual void draw(Uint8 alpha = 255) const;
	virtual void drawIntersection(const Actor& other);

	virtual void translate(float x, float y);
	virtual void translate(math::Vector2D translation);
	virtual void rotate(float angle);
	virtual void scale(float ratio);
	virtual void scale(math::Vector2D ratio);

	virtual math::Vector2D getSize();
	virtual math::AABB getBox();

	virtual void setPosition(float x, float y);
	virtual void setPosition(math::Vector2D position);
	virtual void setAngle(float angle);
	virtual void setScale(math::Vector2D scale);
	virtual void setColor(math::Vector3D color);

	virtual bool testCollision(const Actor& other) const;

	virtual ~Actor(void);
};

