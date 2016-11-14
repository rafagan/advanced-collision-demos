#include "Actor.h"

using namespace std;
using namespace math;
using namespace math::rh;

Actor::Actor(const char* _fileName, int _width, int _height, initializer_list<unsigned int> _frames, float _framerate)
	: frames(_frames), framerate(_framerate), color(Vector3D(255,255,255)), frame(0), timeSpent(0), centered(true)
{
	extern C2D2_SpriteSet sprites[C2D2_MAX_SPRITESET]; //Magia negra
	this->id = C2D2_CarregaSpriteSet(_fileName,_width,_height);
	this->c2d2_sprite = &sprites[id-1];

	size = Vector2D((float)(_width > 0 ? _width : c2d2_sprite->largura), (float)(_height > 0 ? _height : c2d2_sprite->altura));
	box.size = getSize();

	if(frames.empty())
		frames.push_back(0);
	frames.resize(frames.size());

	setAngle(0.0f);
	setPosition(Vector2D());
	setScale(Vector2D(1,1));
}

void Actor::update(float dt)
{
	static long double systemTime = 0.0;
	systemTime += dt;

	world = newAffineTranslation(position) * newAffineRotation(angle) * newAffineScale(myScale.x,myScale.y);
	box.transform(position, angle, getSize(), centered);

	if(frames.size() > 1) {
		if(systemTime > timeSpent + framerate) {
			timeSpent = systemTime;
			frame = frame+1 == frames.size() ? 0 : ++frame;
		}
	}
	else
		frame = 0;

	//Observe a rotação dos AABB
	//rotate(toRadians(30 * dt));
}

void Actor::draw(Uint8 alpha) const {
	int w = (int) size.x;
	int h = (int) size.y;

	Vector2D lim[2];
	if(centered) {
		lim[0].x = -w / 2.0f;
		lim[0].y = -h / 2.0f;
		lim[1].x =  w / 2.0f;
		lim[1].y =  h / 2.0f;
	} else {
		lim[0].x = 0.0f;
		lim[0].y = 0.0f;
		lim[1].x =  (float)w;
		lim[1].y =  (float)h;
	}

	Vector2D p[4] = {
		Vector2D( lim[0].x, lim[0].y ), 
		Vector2D( lim[1].x, lim[0].y ), 
		Vector2D( lim[1].x, lim[1].y ), 
		Vector2D( lim[0].x, lim[1].y )  
	};

	int x[4], y[4];
	for (int i = 0; i < 4; ++i)
	{
		Vector2D pt = transform(world, p[i]);
		x[i] = (int)pt.x;
		y[i] = (int)pt.y;
	}

	C2D2_DesenhaSpriteEfeito(id, frames[frame], x, y, (Uint8) color.x, (Uint8) color.y, (Uint8) color.z, alpha);
	box.draw(Vector3D(255,0,0));
}

void Actor::drawIntersection(const Actor& other)
{
	if(!box.intersects(other.box))
		return;

	auto iBox = box.intersection(other.box);
	AABB_Draw iBoxDraw(iBox); // "Cast"
	iBoxDraw.draw(Vector3D(0,255,0));
}

void Actor::translate(float x, float y)
{
	translate(Vector2D(x, y));
}

void Actor::translate(Vector2D translation)
{
	setPosition(this->position + translation);
}

void Actor::rotate(float _angle)
{
	setAngle(this->angle + _angle);
}

void Actor::scale(float ratio)
{
	setScale(this->myScale + this->myScale * ratio);
}

void Actor::scale(Vector2D ratio)
{
	setScale(Vector2D(ratio.x * myScale.x,ratio.y * myScale.y));
}

Vector2D Actor::getSize()
{
	return Vector2D(myScale.x * size.x, myScale.y * size.y);
}

math::AABB Actor::getBox()
{
	return box;
}

void Actor::setPosition(float x, float y)
{
	setPosition(Vector2D(x, y));
}

void Actor::setPosition(Vector2D _position)
{
	this->position.set(_position) - (centered ? Vector2D(getSize()/2) : Vector2D());
}

void Actor::setAngle(float _angle)
{
	this->angle = _angle;
}

void Actor::setScale(Vector2D _scale)
{
	this->myScale.set(_scale);
}

void Actor::setColor(Vector3D _color)
{
	this->color = _color;
}

bool Actor::testCollision(const Actor& other) const
{
	if(!box.intersects(other.box))
		return false;
	return testBitmaskCollision(other,box.intersection(other.box));
	
	//Se estivessemos utilizando a Chien2D para calcular a colisão...
	//return C2D2_ColidiuSprites(
		//id,frames[frame],position.x,position.y,other.id,frames[other.frame],other.position.x,other.position.y);
}

Actor::~Actor(void)
{
	C2D2_RemoveSpriteSet(id);
}

// Aluno: Como o código é hardcore, desta vez eu vou comentar...

bool Actor::testBitmaskCollision(const Actor& other, AABB& iBox) const
{
	/*
		Calcula qual é a linha e coluna atual do quadro da animação que esta sendo reproduzida.
		Com esta coordenada, conseguiremos saber exatamente qual é a região da imagem em que precisaremos
		calcular o bitmask
	*/
	unsigned int row_col[2];
	fillSpriteIndexRowAndColumn(row_col,*this);
	unsigned int otherRow_col[2];
	fillSpriteIndexRowAndColumn(otherRow_col,other);

	/*
		Precisamos agora iterar sobre cada pixel das duas imagens na área exata da intersecção.
		Se existirem duas cores que não são a Color Key, isso significa que houve colisão.

		Iniciamos o for no início do retângulo de intersecção.
	*/
	for(int i = (int)iBox.top(); i <= iBox.bottom(); i++) {
		/*
			Calcula para o sprite 1 e 2 a coordenada do píxel na imagem em y.
			Essa coordenada é baseada no frame da animação atual somado com o offset.
			Precisamos calcular a subtração para empurar a imagem para o canto (0,0) da tela.
			
			A mesma lógica será aplicada ao x no for interno.
		*/
		int y1 = c2d2_sprite->spAltura * row_col[0] + (int)(i - box.top());
		int y2 = other.c2d2_sprite->spAltura * otherRow_col[0] + (int)(i - other.box.top());

		for(int j = (int)iBox.left(); j <= iBox.right(); j++) {
			int x1 = c2d2_sprite->spLargura * row_col[1] + (int)(j - box.left());
			int x2 = other.c2d2_sprite->spLargura * otherRow_col[1] + (int)(j - other.box.left());

			//Finalmente o teste: Pegamos o valor do pixel na coordenada e verificamos se é a color key
			if(testBitmaskColorKey(getImage(),x1,y1) || testBitmaskColorKey(other.getImage(),x2,y2))
				continue; //Se for a color key, não há colisão... Vamos para o próximo pixel
			return true; //Opa, colisão detectada...
		}
	}
	return false; //Não houve colisão
}

//To com preguição de fazer alocação dinâmica, então vou usar parâmetros por referência
void Actor::fillSpriteIndexRowAndColumn(unsigned int row_col[2], const Actor& actor) const
{
	row_col[0] = actor.frames[actor.frame] / (actor.getImage()->h/actor.c2d2_sprite->spAltura);
	row_col[1] = actor.frames[actor.frame] % (actor.getImage()->w/actor.c2d2_sprite->spLargura);
}

SDL_Surface* Actor::getImage() const
{
	return c2d2_sprite->imagem;
}

bool Actor::isColorKey(Uint32 r, Uint32 g, Uint32 b, Uint32 a) const
{
	return (a == 0);//a < 255; (r == 255 && g == 255 && b == 255)
}

//Funções auxiliares do testBitmaskColorKey
Uint32 getPixel( SDL_Surface *surface, int x, int y )
{
	SDL_LockSurface(surface);
	Uint32 *pixels = (Uint32 *)surface->pixels;
	SDL_UnlockSurface(surface);
	
	//Quem implementou o terreno em CG sabe o que eu estou fazendo...
	return pixels[ ( y * surface->w ) + x ];
}

void putPixel( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
	SDL_LockSurface(surface);
	Uint32 *pixels = (Uint32 *)surface->pixels;
	pixels[ ( y * surface->w ) + x ] = pixel;
	SDL_UnlockSurface(surface);
}
//FIM: Funções auxiliares do testBitmaskColorKey

bool Actor::testBitmaskColorKey(SDL_Surface* image,unsigned int x, unsigned int y) const
{
	auto f = getImage()->format;
	Uint32 pixel = getPixel(image,x,y);
	Uint32 rgba[4];

	rgba[0] = ((pixel & f->Rmask) >> f->Rshift) << f->Rloss;
	rgba[1] = ((pixel & f->Gmask) >> f->Gshift) << f->Gloss;
	rgba[2] = ((pixel & f->Bmask) >> f->Bshift) << f->Bloss;
	rgba[3] = ((pixel & f->Amask) >> f->Ashift) << f->Aloss;

	return isColorKey(rgba[0],rgba[1],rgba[2],rgba[3]);
}
