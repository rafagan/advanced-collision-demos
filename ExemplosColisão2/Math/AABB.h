#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix3.h"
#include <array>

namespace math {
	class BoundingCircle;

	class AABB
	{
	public:
		static AABB newByBounds(float left, float right, float top, float bottom);
		static AABB newByUnion(const AABB& a, const AABB& b);

		/*
		Esta abordagem considera que os valores da posi��o, tamanho, �ngulo e escala devem ficar no AABB
		A vantagem � que possuiremos m�todos mais limpos e o objeto da classe pode ser uma refer�ncia a esses atributos do objeto
		A desvantagem � que eles sempre devem ser atualizados, o que gera duplicata de dados nas classes
		Uma classe cuja fun��o de desenho � realizada no centro da imagem e n�o no canto superior esquerdo pode gerar inconsis�ncia na aplica��o da colis�o caso a mesma posi��o seja utilizada
		Outra forma de resolver o problema seria receber dados como posi��o e tamanho como argumento dos m�todos
		*/
		math::Vector2D position, size;

		explicit AABB() {};
		explicit AABB(float x, float y, float width, float height);
		explicit AABB(math::Vector2D position, math::Vector2D size);
		
		bool contains(const Vector2D& point) const;
		bool contains(const AABB& other) const;
		bool contains(const BoundingCircle& circle) const;

		bool intersects(const AABB& other) const;
		AABB intersection(const AABB& other) const;
		bool intersects(const BoundingCircle& circle) const;

		void transform(math::Vector2D position, float angle, math::Vector2D size, bool centered);

		float left() const;
		float right() const;
		float top() const;
		float bottom() const;

		math::Vector2D getCenter() const;
		std::array<math::Vector2D, 4> getBounds() const;

		virtual void draw(math::Vector3D color) const {};

		virtual ~AABB(void);
	};

	std::ostream& operator<<(std::ostream& output, const AABB&);
}