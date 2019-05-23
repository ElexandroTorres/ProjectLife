#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

#include <canvas.h>

// Função para validar se uma string é um numero.
bool isValidNumber(const std::string number) {
	for(int i = 0; i < number.size(); i++) {
		// Caso o caractere não esteja entre 0 e 9 não será um numero valido.
		if(number[i] < '0' or number[i] > '9') {
			return false; 
		}
	}
	return true;
}

//definição de uma celula.
class Cell {
	private:
		bool c_alive; //!< Estado da célula, true significa celula viva e false celula morta.
		short c_numberOfNeighbors; //!< Quantidade de vizinhos atuais da célula que estão vivos.
	public:
		/*
		 * Construtor padrão, inicializando a célula como morta.
		*/
		Cell(bool alive = false) {
			c_alive = alive;
			c_numberOfNeighbors = 0;
		}
		/*
		 * Construtor copia.
		*/
		Cell(const Cell &clone) {
          c_alive = clone.c_alive;
          c_numberOfNeighbors = clone.c_numberOfNeighbors;
        }
        /*
         * Destrutor padrão.
        */
		~Cell() = default;
		/*
         * Atribui um estado para a celula.
         * @param state, booleano representado o estado da célula. True para viva e false para morta.
		*/
		void set_state(bool state) {
			c_alive = state;
		}
		/*
		 * Verifica se a célula está viva.
		 * @return true caso esteja viva e false caso contrario.
		*/
		bool is_alive() {
			return c_alive;
		}
		/*
		 * "Mata" a célula definindo seu estado para false.
		*/
		void kill() {
			c_alive = false;
		}
		/*
		 * Faz "nascer" uma célula definindo seu estado para true.
		*/
		void born() {
			c_alive = true;
		}
		/*
         * Define a quantidade de vizinhos vivos da célula.
         * @param n, numero de vizinhos vivos.
		*/
		void set_neighbors(short n) {
			c_numberOfNeighbors = n;
		}
		/*
		 * Retorna o numero de vizinhos vivos da célula.
		 * @return quantidade de vizinhos vivos.
		*/
		short neighbors() {
			return c_numberOfNeighbors;
		}
};


class Life {

	private:
		int m_argc; //!< Quantidade de argumentos passados por linha de comando.
		std::vector<std::string> m_argv; //!< Lista de argumentos passados por linha de comando.
		
		std::string m_line;
		int m_height;
		int m_width;
		char m_vivo;

		int m_currentGeneration = 1;


		std::vector<Cell> cells; //!< Lista de células da simulação.
		std::vector<life::Coordenada> liveCells; //<! Lista de células vivas da simulação.
		std::vector<Cell> cellsCopy; //<! Copia do liveCells.

		std::string m_imagesDirectory = "none";
		int m_maxGen = -1;
		int m_fps = 2; //<! Numero de fps das exibições das celulas, caso padrão será.
		int m_blockSize = 5;

		std::vector<std::string> m_generationData;

	public:
		/*
		 * Construtor padrão.
		 * @param argc, quantidade de argumentos passados por linha de comando.
		 * @param argv, lista de argumentos passados por linha de comando.
		*/
		Life(int argc, const char *argv[]) {
			m_argc = argc;
			m_argv.resize(argc);
			// Passar os argumentos para um vector de strings para facilitar a manipulação posteriomente. 		
			for(int i = 0; i < m_argc; i++) {
				m_argv[i] = argv[i];
			}
		}
		/*
		 * Destrutor padrão.
		*/
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

		/*
		 * Imprime a matriz de células na saida padrão.
		*/
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
		/*
		 * Carrega as configurações passadas no arquivo.
		 * @param arquivo, arquivo de configuração.
		*/
		void carregar_configuracoes(std::fstream &config) {
			config >> m_height; // Ler o numero de linhas(altura) da "imagem".
			config >> m_width; // Ler o numero de colunas(largura) da "imagem".
			config >> m_vivo; // Ler o caractere que irá representar uma celula viva.
			
			cells.resize(m_height*m_width); // Redefine o tamanho de cells para armazenar todos as células.
			cellsCopy.resize(m_height*m_width); // Redefine o tamanho da copia.
			//Varre todo o arquivo em busca das celulas vivas e mortas e redefine seu estado.
			int row = 0;
			while(config >> m_line and row < m_height) {
				for(auto column = 0u; column < m_line.size(); column++) {
					if(column < m_width) {
						/* Toda vez que for encontrado o caractere que representa as células vivas será definido o estado
						da céula como viva e caso o contrario como morta. */
						if(m_line[column] == m_vivo) { 
							cells[column + m_width * row].set_state(true);	
						}
						else{
							cells[column + m_width * row].set_state(false);
						}	
					}
				}
				row++;
			}
		}
		/*
		 * Valida os argumentos passados pela linha de comando, retornando falso caso não sejam validos ou insuficientes.
		 * @return true caso todos os argumentos sejam validados e false caso contrario.
		*/
		bool validar_argumentos(void) {
			// Caso não seja passado nenhum argumento de configuração.
			if(m_argc == 1) {
				return false;
			}
			// Verificar se o argumento de configuração passado é o "--help";
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
			/*
			std::fstream arquivo(m_argv[1]);
			if(arquivo.is_open()) { //caso o arquivo exista...
				carregar_configuracoes(arquivo);
				arquivo.close();
			}
			else {
				std::cout << "arquivo informado não existe!\n";
			}
			*/
			
			// Varrer todos os argumentos.
			for(int i = 1; i < m_argc; i++) {
				if(m_argv[i] == "--imgdir") {
					m_imagesDirectory = m_argv[++i];
					std::cout << "Diretorio: " << m_imagesDirectory << "\n"; 
				}
				else if(m_argv[i] == "--maxgen") {
					// Verificar se o argumento seguinte é um numero valido.
					if(isValidNumber(m_argv[++i])) {
						m_maxGen = std::stoi(m_argv[i]);
						std::cout << "numero de gerações: " << m_maxGen << std::endl;
					}
					else {
						std::cout << m_argv[i] << " it's not a valid number. Use --help to see the valid options.\n";
						return false;
					}
					
				}
				else if(m_argv[i] == "--fps") {
					// Verificar se o argumento seguinte é um numero valido.
					if(isValidNumber(m_argv[++i])) {
						m_fps = std::stoi(m_argv[i]);
						std::cout << "numero de fps: " << m_fps << std::endl;
					}
					else {
						std::cout << m_argv[i] << " it's not a valid number. Use --help to see the valid options.\n";
						return false;
					}
				}
				else if(m_argv[i] == "--blocksize") {
					// Verificar se o argumento seguinte é um numero valido.
					if(isValidNumber(m_argv[++i])) {
						m_blockSize = std::stoi(m_argv[i]);
						std::cout << "tamanho do bloco: " << m_blockSize << std::endl;
					}
					else {
						std::cout << m_argv[i] << " it's not a valid number. Use --help to see the valid options.\n";
						return false;	
					}
				}
				else if(m_argv[i] == "--bkgcolor <color>") {
					//TODO.
				}
				else if(m_argv[i] == "--alivecolor <color>") {
					//TODO.
				}
				else if(m_argv[i] == "--outfile <filename>") {
					//TODO.
				}
				else {
					std::fstream config(m_argv[i]);
					// Verificar se foi possivel abrir o arquivo.
					if(config.is_open()) { 
						carregar_configuracoes(config);
						config.close();
					}
					else {
						std::cout << "Informed file does not exist.\n";
						return false;
					}
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
			if(not(i-1 < 0)) {
				if(not(j-1 < 0)) {
					if(cells[(i-1) + m_width*(j-1)].is_alive()) {
						qntVizinhos++;
					}	
				}
				if(!(j+1 >= m_height)) {
					if(cells[(i-1) + m_width*(j+1)].is_alive()) {
						qntVizinhos++;
					}	
				}
				if(cells[(i-1) + m_width*j].is_alive()) {
					qntVizinhos++;
				}
				
			}

			if(!(i+1 >= m_width)) {
				if(!(j-1 < 0)) {
					if(cells[(i+1) + m_width*(j-1)].is_alive()) {
						qntVizinhos++;
					}	
				}
				if(!(j+1 >= m_height)) {
					if(cells[(i+1) + m_width*(j+1)].is_alive()) {
						qntVizinhos++;
					}	
				}
				if(cells[(i+1) + m_width*j].is_alive()) {
					qntVizinhos++;
				}
			}
			if(!(j-1 < 0)) {
				if(cells[i + m_width*(j-1)].is_alive()) {
					qntVizinhos++;
				}	
			}
			if(!(j+1 >= m_height)) {
				if(cells[i + m_width*(j+1)].is_alive()) {
					qntVizinhos++;
				}	
			}
			
			return qntVizinhos;

		}

		/*
		 * Atualiza a lista de células vivas.
		 * @param lista de células.
		*/
		void update_liveCells(std::vector<Cell> &c) {
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
		/*
		 * Salva a lista de células vivas em um arquivo para poder consulta-las posteriomente.
		 * @param numge, Numero da geração atual.
		*/
		void save_generations() {
			//liveCells[i].get_x(), liveCells[i].get_y()
			std::string currentGeneration = "";
			for(auto i = 0u; i < liveCells.size(); i++) {
				currentGeneration += std::to_string(liveCells[i].get_x()) + " " + std::to_string(liveCells[i].get_y()) + " ";	
			}

			m_generationData.push_back(currentGeneration);
			
		}
		/*TODO*/
		void process_simulation() {
			
			update_liveCells(cells); // Verifica quais as células que estão vivas.
			
			save_generations(); //Adiciona as celulas vivas a um arquivo com um identificador de qual geração ela pertence.
			
			cellsCopy = cells;
				
			// Verifica e define quantos vizinhos cada célula tem.
			for(int j = 0; j < m_height; j++) { 
				for(int i = 0; i < m_width; i++) {
					cells[i + m_width*j].set_neighbors(checarVizinhos(i, j));
				}
			}
			// Verifica quais células irão mudar o seu estado.
			for(int j = 0; j < m_height; j++) {
				for(int i  = 0; i < m_width; i++) {
					// Caso a célula esteja morta, verificar se ela irá "nascer".
					if(not cells[i +m_width*j].is_alive() and cells[i +m_width*j].neighbors() == 3) {
						cellsCopy[i +m_width*j].born();
					}
					// Caso a célula esteja viva, verificar se ela continuarar a viver.(NOT TODAY).
					else if(cells[i +m_width*j].is_alive() and (cells[i +m_width*j].neighbors() < 2 or cells[i +m_width*j].neighbors() > 3)) {
						cellsCopy[i +m_width*j].kill();
					}
				}
			}

			cells = cellsCopy;
			//fazer função para gravar a iamgem.
								
			std::string filename;
			filename = "Generation " + std::to_string(m_currentGeneration);
				
			Canvas img(m_width, m_height, 10);
			//pintar todos os pixels, teste.
			//descobrir valor da coluna.
			for(auto i = 0u; i < liveCells.size(); i++) {
				//std::cout << "valores das coordenadas: \n";
				//std::cout << "X: " << liveCells[i].get_x() << " Y: " << liveCells[i].get_y() << "\n"; 
				img.set_pixel(liveCells[i].get_x(), liveCells[i].get_y() , life::RED );
			}
			encode_png(filename + ".png", img.pixels(), (unsigned) img.get_width(), (unsigned) img.get_height());	
			m_currentGeneration++;
		
		}
		
		bool is_stable() {
			for(int i = 0; i < m_generationData.size() - 1; i++) {
				/* Verificar se a ultima geração adicionada(no caso a atual) é igual a alguma outra.
				   Caso seja, significa que a geração atual é estavel. */
				if(m_generationData[m_generationData.size()-1] == m_generationData[i]) {
					std::cout << "Stable in generation " << i+1 << "\n";
					return true;
				}
			}
			return false;
			
		}
		

		//caso a simulação termine.
		bool end_simulation() {
			//verifica se é estavel.
			//verifica se é extinta.
			if(m_maxGen != 0) {
				process_simulation(); 
				if(is_stable()) {
					std::cout << "STABLE!!!\n";
					return true;
				}
				m_maxGen--;	
				return false; //simulação não terminou.	
			}
    		//VAI RODAR PRA SEMPRE, ATÉ ENCONTRAR STABLE.
			//return true;
			//verificar se é estavel.
			//verificar se é extinta;
			//verificar se o numero total de gerações ja foi executado.
			//caso alguma dessas operações tenha acontecido, retorne true.
			//caso nenhuma tenha acontecido ainda, a simuação continua, ou seja, retorna false.
		}


};


#endif