#pragma once

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>

#include "Math/MathIncluder.h"
#include "Actor.h"

using namespace math;
using namespace std;

class GameLoop
{
private:
	C2D2_Botao *keys;
	C2D2_Mouse *mouse;
public:
	explicit GameLoop(void);
	GameLoop& init();
	int run();
	virtual ~GameLoop(void);
};

