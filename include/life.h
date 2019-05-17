#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

#include <canvas.h>

//definição de uma celula.
class Cell {
	private:
		bool c_alive; // Estado da celula, true significa celula viva e false celula morta.
		short c_numberOfNeighbors;
	public:
		Cell(bool alive = false) {
			c_alive = alive;
			c_numberOfNeighbors = 0;
		}
		Cell(const Cell &clone) {
          c_alive = clone.c_alive;
          c_numberOfNeighbors = clone.c_numberOfNeighbors;
        }
		~Cell() = default;

		void set_state(bool state) {
			c_alive = state;
		}

		bool is_alive() {
			return c_alive;
		}
		//mata uma celula.
		void kill() {
			c_alive = false;
		}

		void born() {
			c_alive = true;
		}

		void set_neighbors(short n) {
			c_numberOfNeighbors = n;
		}
		
		//checa quantos vizinhos vivos a celula tem.
		short neighbors() {
			return c_numberOfNeighbors;
		}
};



class Life {

	private:
		int m_argc;
		std::vector<std::string> m_argv;
		
		std::string m_line;
		int m_height;
		int m_width;
		char m_vivo;


		std::vector<Cell> cells;
		std::vector<life::Coordenada> liveCells; //vetor que ira guardar a posição da celula viva.
		std::vector<Cell> cellsCopy;

	public:
		//Construtor padrão.
		Life(int argc, const char *argv[]) {
			m_argc = argc;
			m_argv.resize(argc);		
			for(int i = 0; i < m_argc; i++) {
				m_argv[i] = argv[i];
			}
		}

		~Life() = default;
		
		// Example 1
		// Encode from raw pixels to disk with a single function call
		// The image argument has width * height RGBA pixels or width * height * 4 bytes
		void encode_png(const std::string filename/*const char* filename*/, const unsigned char * image, unsigned width, unsigned height) {

    		//Encode the image
    		unsigned error = lodepng::encode(filename, image, width, height);

    		//if there's an error, display it
    		if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
		}

		//Mostra a matriz, caso seja possivel.
		void print() {
			std::cout << "Impressão da matriz: \n\n";
			for(int j = 0; j < m_height; j++) {
				std::cout << "| ";
				for(int i = 0; i < m_width; i++) {
					if(cells[i + m_width * j].is_alive()) {
						std::cout << "*";
					}
					else {
						std::cout << " ";	
					}
				}
				std::cout << " |\n";
			}
		}

		void carregar_configuracoes(std::fstream &arquivo) {
			arquivo >> m_height; // Ler o numero de linhas(altura) da "imagem".
			arquivo >> m_width; // Ler o numero de colunas(largura) da "imagem".
			arquivo >> m_vivo; // Ler o caractere que irá representar uma celula viva.
			std::cout << "Linhas: " << m_height << " | colunas: " << m_width << " | vivo: " << m_vivo << "linhas + colunas = " << m_height + m_width<< "\n";
			
			cells.resize(m_height*m_width);//
			cellsCopy.resize(m_height*m_width);
			//teste criar imagem.

			int j = 0;
			while(arquivo >> m_line and j < m_height) {
				for(auto i = 0u; i < m_line.size(); i++) {
					// Apenas os caracteres que representam as celulas vivas serão incluidos.
					if(m_line[i] == m_vivo) { 
						cells[i + m_width * j].set_state(true);	
					}
					else{
						cells[i + m_width * j].set_state(false);
					}
				}
				j++;
			}

		}
		

		/*
		 * Valida os argumentos apssados pela linha de comando, retornando falso caso não sejam validos e insuficientes.
		*/
		bool validar_argumentos(void) {
			// Caso não seja passado nenhum argumento de configuração.
			if(m_argc == 1) {
				return false;
			}
			//verificar se o argumento de configuração passado é o "--help";
			if(m_argv[1] == "--help") {
				//Mostrar mensagem de ajuda.
				std::cout << "Usage: glife <input_config_file> [<options>]\n";
				std::cout << "  Simulation options:\n";
				std::cout << "    --help                 Print this help text.\n";
				std::cout << "    --imgdir <path>        Specify directory where output images are written to\n";
				std::cout << "    --maxgen <num>         Maximum number of generations to simulate.\n";
				std::cout << "    --fps <num>            Number of generations presented per second.\n";
				std::cout << "    --blocksize <num>      Pixel size of a cell. Default = 5.\n";
				std::cout << "    --bkgcolor <color>     Color name for the background. Default GREEN.\n";
				std::cout << "    --alivecolor <color>   Color name for representing alive cells. Default RED.\n";
				std::cout << "    --outfile <filename>   Write the text representation of the simulation to the given filename.\n\n\n";

				std::cout << "  Avaliable colors are:\n";
				std::cout << "    BLACK BLUE CRIMSON DARK_GREEN DEEP_SKY_BLUE DODGER_BLUE\n";
				std::cout << "    GREEN LIGHT_BLUE LIGHT_GREY LIGHT_YELLOW RED STEEL_BLUE\n";
				std::cout << "    WHITE YELLOW\n";
							  	

				return false;
			}
			//COnsiderar que o primeiro argumento de configuração vai ser o nome do arquivo.
			std::fstream arquivo(m_argv[1]);
			if(arquivo.is_open()) { //caso o arquivo exista...
				carregar_configuracoes(arquivo);
				arquivo.close();
			}
			else {
				std::cout << "arquivo informado não existe!\n";
			}
			
			//varrer todo o vetor de argumentos.
			for(int i = 2; i < m_argc; i++) {
				if(m_argv[i] == "--imgdir") {
					//verificar se segue o argumento com um diretorio.
					//acho que criando um arquivo e especificando onde ele fica será criado uma pasta.
				}
				if(m_argv[i] == "--maxgen") {
					int m_numGeracoes = std::stoi(m_argv[i+1]);
					std::cout << "numero de gerações: " << m_numGeracoes << std::endl;
				}
				if(m_argv[i] == "--fps") {
					int m_numfps = std::stoi(m_argv[i+1]);
				}
				if(m_argv[i] == "--blocksize") {
					int m_blocksize = std::stoi(m_argv[i+1]);
				}

			}
			
			
			//deletar o vetor dinmaico criado aqui ao inves de no desconstrutor.
			return true;
		}


		bool start(void) {
			//Se os argumentos não forem validados.
			if(!validar_argumentos()) {
				return false;
			}
			//caso os argumentos sejam validados.
			return true;

			
		}

		short checarVizinhos(int i, int j) {
			short qntVizinhos = 0;
			//vizinhos de itens nas bordas.
			//siginifica que esta na borda.
			/*
			if(i == m_height-1 or i == 0 or j == 0 or j == m_width-1) {
				if(i == 0 and j == 0) {
					if(image[i + m_width*(j+1)] == m_vivo) {
						qntVizinhos++;
					}
					if(image[(i+1) + m_width*j] == m_vivo) {
						qntVizinhos++;
					}
					if(image[(i+1) + m_width*(j+1)] == m_vivo) {
						qntVizinhos++;
					}
					return qntVizinhos;	
				}
				//
				if(i == 0 and j == m_width-1) {
					if(image[i + m_width*(j+1)] == m_vivo) {
						qntVizinhos++;
					}
					if(image[(i-1) + m_width*j] == m_vivo) {
						qntVizinhos++;
					}
					if(image[(i-1) + m_width*(j+1)] == m_vivo) {
						qntVizinhos++;
					}
					return qntVizinhos;	
				}
				//
				if(i == m_height-1 and j == 0) {
					if(image[i + m_width*(j-1)] == m_vivo) {
						qntVizinhos++;
					}
					if(image[(i-1) + m_width*j] == m_vivo) {
						qntVizinhos++;
					}
					if(image[(i-1) + m_width*(j-1)] == m_vivo) {
						qntVizinhos++;
					}
					return qntVizinhos;	
				}
				if(i == m_height-1 and j == m_width-1) {
					if(image[i + m_width*(j-1)] == m_vivo) {
						qntVizinhos++;
					}
					if(image[(i-1) + m_width*j] == m_vivo) {
						qntVizinhos++;
					}
					if(image[(i+1) + m_width*(j+1)] == m_vivo) {
						qntVizinhos++;
					}
					return qntVizinhos;	
				}
			}
	*/
			//caso esteja nas laterais.

					

				
			
			//casos especiais.
			//celula nos cantos diagonais.
			//i = 0; j = 0;
			//ANTES FAZER O BASICO.
			if(cells[(i-1) + m_width*(j-1)].is_alive()) {
				qntVizinhos++;
			}
			if(cells[(i-1) + m_width*j].is_alive()) {
				qntVizinhos++;
			}
			if(cells[(i-1) + m_width*(j+1)].is_alive()) {
				qntVizinhos++;
			}
			if(cells[i + m_width*(j-1)].is_alive()) {
				qntVizinhos++;
			}
			if(cells[i + m_width*(j+1)].is_alive()) {
				qntVizinhos++;
			}
			if(cells[(i+1) + m_width*(j-1)].is_alive()) {
				qntVizinhos++;
			}
			if(cells[(i+1) + m_width*j].is_alive()) {
				qntVizinhos++;
			}
			if(cells[(i+1) + m_width*(j+1)].is_alive()) {
				qntVizinhos++;
			}

			return qntVizinhos;

		}


		void updateLiveCells(std::vector<Cell> &c) {
			//checar quais as celuas estão vivas.
			//inicialmente limpar o vetor.
			if(liveCells.size() > 0) {
				liveCells.clear();	
			}
			for(int j = 0; j < m_height; j++) {
				for(int i = 0; i < m_width; i++) {
					if(cells[i + m_width * j].is_alive()) { //se a cellula estiver viva, salvar a posição dela.
						liveCells.push_back(life::Coordenada(j, i));
					}
				}
			}

		}
		
		void vetorVivos(int numge) { //numge, numero da geração.
			std::fstream teste;
			//caso seja  a primera geração. criar um arquivo apenas como modo de escrita.
			if(numge == 1) {
				teste.open("saida.txt", std::fstream::out /*std::fstream::trunc*/);
			}
			else {
				teste.open("saida.txt", std::fstream::app);	
			}
			teste << numge << " " << liveCells.size() << " ";
			for(auto i = 0u; i < liveCells.size(); i++) {
				teste << liveCells[i] << " ";	
			}
			teste << "\n";
			
			teste.close();
		}

		

		//sabendo o numero de celulas vivas, vamos declarar

		void process_simulation() {
			int x = 1;
			while(x < 10) {
				updateLiveCells(cells);
				//copiar a imagem atual para a copia.
				vetorVivos(x);
				cellsCopy = cells;
				
				print(); //mostrar a imagem.
				

				//checar a quantidade de vivos.
				//std::cout << "Numero de celulas vivas: " << liveCells.size() << "\n";
				//vetorVivos(x);
				/*
				std::cout << "celulas vivas: \n";
				for(int i = 0; i < liveCells.size(); i++) {
					std::cout << liveCells[i] << " ";
				}
				std::cout << "\n";
				*/
				
				//Contar a quantidade de vizinhos de cada celula.
				for(int j = 0; j < m_height; j++) { //começar de 0, 1 é teste.
					for(int i = 0; i < m_width; i++) { //começar de 0, 1 é teste, ir até m_width, por enquanto é teste.
						cells[i + m_width*j].set_neighbors(checarVizinhos(i, j)); //tetorna a quantidade de vizinhos desta celula.
					}
				}


				//procurar quem tem exatamente 3 vizinhos para viver.
				//sobrevive se tem 2 ou 3.
				//e morre caso contrario.
				for(int j = 0; j < m_height; j++) {
					for(int i  = 0; i < m_width; i++) {
						if(not cells[i +m_width*j].is_alive() and cells[i +m_width*j].neighbors() == 3) {
							cellsCopy[i +m_width*j].born();
						}
						else if(cells[i +m_width*j].is_alive() and (cells[i +m_width*j].neighbors() < 2 or cells[i +m_width*j].neighbors() > 3)) {
							cellsCopy[i +m_width*j].kill();
						}
					}
				}

					
				cells = cellsCopy;

				//print();
				
				
				std::string filename;
				filename = "Generation " + std::to_string(x);
				
				Canvas img( m_width, m_height, 100);
			//pintar todos os pixels, teste.
				//descobrir valor da coluna.
				for(auto i = 0u; i < liveCells.size(); i++) {
					//std::cout << "valores das coordenadas: \n";
					//std::cout << "X: " << liveCells[i].get_x() << " Y: " << liveCells[i].get_y() << "\n"; 
					img.set_pixel(liveCells[i].get_x(), liveCells[i].get_y() , life::RED );
					

				}
					encode_png(filename + ".png", img.pixels(), (unsigned) img.get_width(), (unsigned) img.get_height() );	
			

	    		x++;
	    		
			}
			std::cerr << "CHEGOUA AKI!!\n";

			//remove("saida.txt");
			//gerar as imagens, ou arquivos de texto ou console.
		}

		



		//caso a simulação termine.
		bool end_simulation() {
			process_simulation(); //porenquanto
			//teste
			//Canvas img( 50, 50, 30);
    		//largura x altura...
    		
			std::cerr << "CHEOGU AKI TBM\n";
			return true;
			//verificar se é estavel.
			//verificar se é extinta;
			//verificar se o numero total de gerações ja foi executado.
			//caso alguma dessas operações tenha acontecido, retorne true.
			//caso nenhuma tenha acontecido ainda, a simuação continua, ou seja, retorna false.
		}


};

#endif