#include "Bitmask.h"

using namespace math;

function<bool(ofVec4f)> Bitmask::defaultColorKey()
{
	return [](ofVec4f colorKey) -> bool {
		return colorKey.w == 0;
	};
}

ofVec4f Bitmask::pixelColor(int x, int y) const
{
	auto& pixels = image->getPixels();
	int index = y * image->getWidth() + x;
	
	ofVec4f result;
	result.x = pixels[index * 4 + 1];
	result.y = pixels[index * 4 + 2];
	result.z = pixels[index * 4 + 3];
	result.w = pixels[index * 4 + 4];

	return result;
}

Bitmask::Bitmask(): image(nullptr), broadPhaseBox(nullptr), dimensions(nullptr), frames(nullptr), frame(nullptr)
{
	isColorKey = defaultColorKey();
}

Bitmask::Bitmask(
	ofImage& _image, math::AABB& _broadPhaseBox, 
	Vector2D* _dimensions, vector<unsigned int>* _frames, unsigned int* _frame, function<bool(ofVec4f)> _isColorKey)
	: image(&_image), broadPhaseBox(&_broadPhaseBox), frames(_frames), frame(_frame)
{
	auto zeroVec = Vector2D();
	dimensions = _dimensions == nullptr ? &zeroVec : _dimensions;

	if(dimensions->sizeSqr() == 0 || dimensions->sizeSqr() > math::Vector2D(image->getWidth(), image->getHeight()).sizeSqr()) {
		dimensions->x = image->getWidth();
		dimensions->y = image->getHeight();
	}
	isColorKey = _isColorKey ? _isColorKey : defaultColorKey();
}

bool Bitmask::testCollision(const Bitmask& other) const
{
	//AABB intersection region to apply the bitmask check
	auto region = broadPhaseBox->intersection(*other.broadPhaseBox);
	
	/*
	Calculates which is the current row and column of the frame of the animation being played. 
	With this coordinate, we will be able to know exactly which 
	  is the sprite region of the image in which we will need to calculate bitmask
	*/
	//int rowFrame1 = (*frames)[*frame] / (image->getHeight() / dimensions->y);
	//int colFrame1 = (*frames)[*frame] % int((image->getWidth() / dimensions->x));
	//int rowFrame2 = (*other.frames)[*other.frame] / (other.image->getHeight() / other.dimensions->y);
	//int colFrame2 = (*other.frames)[*other.frame] % int((other.image->getWidth() / other.dimensions->x));

	int rowFrame1, rowFrame2, colFrame1, colFrame2;
	rowFrame1 = rowFrame2 = colFrame1 = colFrame2 = 0;

	/*
	We now need to iterate over each pixel of the two images in the exact area of the intersection. 
	If there are two colors other than Color Key, this means that there was a collision. 
	We begin the for at the beginning of the intersection rectangle.
	*/
	for (auto i = int(region.bottom()); i <= int(region.top()); i++) {
		/*
		Calculates for the sprite 1 and 2 the coordinate of the pixel in the y-image.
		This coordinate is based on the current animation frame plus the offset. 
		We need to calculate the subtraction to push the image to the corner (0,0) of the screen. 
		The same logic will be applied to x in the internal for.
		*/
		int y1 = dimensions->y * rowFrame1       + int(i - broadPhaseBox->bottom());
		int y2 = other.dimensions->y * rowFrame2 + int(i - other.broadPhaseBox->bottom());

		for (auto j = int(region.left()); j <= int(region.right()); j++) {
			int x1 = dimensions->x * colFrame1       + int(j - broadPhaseBox->left());
			int x2 = other.dimensions->x * colFrame2 + int(j - other.broadPhaseBox->left());

			//If this pixel is the color key in any of the images, it's not a collision. Else, pixel collision detected
			if (isColorKey(pixelColor(x1, y1)) || isColorKey(other.pixelColor(x2, y2))) continue;
			
			//TODO: Collision detected, but just with one pixel isn't too perfect?
			return true;
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
