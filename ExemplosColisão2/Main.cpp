#include "GameLoop.h"

#include <ctime>
#include <tchar.h>


//Pr�ximos passos
//1- Possibilidade de aplicar colis�o de bitmask com sprites redimensionados (escala vari�vel)
//2- Implementar colis�o entre dois sprites com bitmask customizada (uma textura, por exemplo). 
	//Excelente para gera��o de cen�rios
//3- Implementar colis�o com remo��o da m�scara de bits
	//O sprite deve ser desenhado apenas nas regi�es em que a m�scara de bits existe
	//Stencyl Buffer
//4- Considerar o c�lculo de rota��o para o Bitmask

int main(int narg, char **valarg)
{
	_tsetlocale(LC_ALL, _T("portuguese_brazil"));
	srand((unsigned int)time(nullptr));

	return GameLoop().init().run();
}