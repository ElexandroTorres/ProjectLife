#include "../include/life.h"




int main(int argc, const char *argv[]) {

	
	//Inicia o jogo com as configurações passadas por argumento.
	Life life(argc, argv); //Instancia um objeto do tipo Life passando os parametros como argumentos.

	//Se a função start retorna false, significa que o programa não foi bem.
	if(!life.start()) {
		return 0;
	}

	while(!life.end_simulation()) {
		//life.process_simulation();
		//porenquanto
		//verificar se é estavel.
		//verificar se é extinta.
	}

	return 0;
}