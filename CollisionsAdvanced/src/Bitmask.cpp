#include "Bitmask.h"

function<bool(ofVec4f)> Bitmask::defaultColorKey()
{
	return [](ofVec4f colorKey) -> bool {
		return colorKey.w == 0;
	};
}

Bitmask::Bitmask(): image(nullptr), broadPhaseBox(nullptr)
{
	isColorKey = defaultColorKey();
}

Bitmask::Bitmask(ofImage& _image, math::AABB& _broadPhaseBox, function<bool(ofVec4f)> _isColorKey)
	: image(&_image), broadPhaseBox(&_broadPhaseBox) 
{
	isColorKey = _isColorKey ? _isColorKey : defaultColorKey();
}

bool Bitmask::testCollision(const Bitmask& other) const
{
	cout << isColorKey(ofVec4f(0, 222, 0, 1)) << endl;

	auto region = broadPhaseBox->intersection(*other.broadPhaseBox);

	for (auto i = int(region.bottom()); i <= int(region.top()); i++) {


		for (auto j = int(region.left()); j <= int(region.right()); j++) {

		}
	}
	return false;
}

void Bitmask::transform(math::Vector2D _position, float angle, math::Vector2D _size, bool centered)
{
	//TODO: Possibilidade de aplicar colisão de bitmask com sprites redimensionados (escala variável)
	//TODO: Considerar o cálculo de rotação para o Bitmask
}

void Bitmask::removeArea(math::AABB& region)
{
	//TODO: utilizar canal alpha para esconder informações
}

void Bitmask::removeArea(math::BoundingCircle& region)
{
	//TODO: utilizar canal alpha para esconder informações
}

Bitmask::~Bitmask()
{
}
