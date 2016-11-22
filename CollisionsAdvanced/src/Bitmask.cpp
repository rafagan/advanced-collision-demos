#include "Bitmask.h"
#include <of3dGraphics.h>

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
	auto color = pixels.getColor(x, y);

	return ofVec4f(color.r, color.g, color.b, color.a);
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

		Image pixels are read with y inverted, so we need to get a coordinate from top to bottom
		*/
		int y1 = image->getHeight() - (dimensions->y * rowFrame1             + i - int(broadPhaseBox->bottom()));
		padValue(y1, 0, int(image->getHeight()) - 1);
		int y2 = other.image->getHeight() - (other.dimensions->y * rowFrame2 + i - int(other.broadPhaseBox->bottom()));
		padValue(y2, 0, int(other.image->getHeight()) - 1);

		for (auto j = int(region.left()); j <= int(region.right()); j++) {
			int x1 = dimensions->x * colFrame1       + j - int(broadPhaseBox->left());
			padValue(x1, 0, int(image->getWidth()) - 1);
			int x2 = other.dimensions->x * colFrame2 + j - int(other.broadPhaseBox->left());
			padValue(x2, 0, int(image->getWidth()) - 1);

			//If this pixel is the color key in any of the images, it's not a collision. Else, pixel collision detected
			if (isColorKey(pixelColor(x1, y1)) || other.isColorKey(other.pixelColor(x2, y2))) 
				continue;
			
//			if (!isColorKey(pixelColor(x1, y1)))
//				cout << "Cor da amarela não passou. Essa cor TEM QUE SER 255 242 0 255, senão é bug: " << pixelColor(x1, y1) << endl;
//			if (!other.isColorKey(other.pixelColor(x2, y2)))
//				cout << "Cor da branca não passou. Essa cor NÃO PODE ter g > 120, senão é bug: " << other.pixelColor(x2, y2) << endl;

			auto& pixels = image->getPixels();
			auto color = pixels.getColor(x1, y1);
			color.r = color.g = color.b = 0;
			pixels.setColor(x1, y1, color);

			//TODO: Collision detected, but just with one pixel isn't too perfect?
			//return true;
		}
	}

	image->update();

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
