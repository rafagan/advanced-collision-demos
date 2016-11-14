#include "GameLoop.h"

#include <ctime>
#include <tchar.h>


//Próximos passos
//1- Possibilidade de aplicar colisão de bitmask com sprites redimensionados (escala variável)
//2- Implementar colisão entre dois sprites com bitmask customizada (uma textura, por exemplo). 
	//Excelente para geração de cenários
//3- Implementar colisão com remoção da máscara de bits
	//O sprite deve ser desenhado apenas nas regiões em que a máscara de bits existe
	//Stencyl Buffer
//4- Considerar o cálculo de rotação para o Bitmask

int main(int narg, char **valarg)
{
	_tsetlocale(LC_ALL, _T("portuguese_brazil"));
	srand((unsigned int)time(nullptr));

	return GameLoop().init().run();
}