#include "GameLoop.h"
#include "IScreen.h"
#include "Exemplos/ExemploBitmask.h"
#include "Exemplos/ExemploAABBRotacao.h"
#include "Exemplos/ExemploUniaoPoligonos.h"

#include "Math/MathIncluder.h"
#include "BoundingCircle_Draw.h"

GameLoop::GameLoop(void)
{
}

GameLoop& GameLoop::init()
{
	if(!C2D2_Inicia(1200, 768, C2D2_JANELA, C2D2_DESENHO_OPENGL, "Exemplos avancados - colisao"))
		printf("Falhou ao iniciar a Chien2D 2. Encerrando o programa.\n");
	C2D2P_Inicia();
	C2D2_TrocaCorLimpezaTela(0, 0, 0);

	keys = C2D2_PegaTeclas();
	mouse = C2D2_PegaMouse();

	return *this;
}

int GameLoop::run()
{
	/*ALUNO: modifique esta variável para inicializar o exemplo*/
	IScreen* screen = new ExemploAABBRotacao();
	screen->init();

	int initialTime = C2D2_TempoSistema();
	int finalTime = 0;
	do {
		finalTime = C2D2_TempoSistema();
		float dt = (finalTime - initialTime) / 1000.0f;
		initialTime = finalTime;

		try {
			IScreen* next = screen->nextScreen();

			if(next == nullptr)
				break;
			else if(next != screen) {
				screen->close();
				delete screen;

				screen = next;
				screen->init();
			}

			screen->update(dt);

			C2D2_LimpaTela();
			screen->draw();
			C2D2_Sincroniza(60);
		} catch(exception& e) {
			cerr << "Exception: " << e.what() << endl;
			exit(1);
		}
	} while(!keys[C2D2_ENCERRA].pressionado && !keys[C2D2_ESC].pressionado);

	screen->close();
	delete screen;
	return 0;
}

GameLoop::~GameLoop(void)
{
	C2D2_Encerra();
}