#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

#include <canvas.h>

/*
 * Valida uma string como representação de um numero.
 * @param number string que representa o número.
 * @return true caso seja um numero valido e false caso contrario.
*/
bool isValidNumber(const std::string number);
/*
 * Função para gerar a imagem.
 * @param filename, o nome da imagem.
 * @param image, tabela de pixels da imagem.
 * @param width, Largura da imagem.
 * @param height, Altura da imagem.
*/
void encode_png(const std::string filename/*const char* filename*/, const unsigned char * image, unsigned width, unsigned height);




class Life {

	private:
		int m_argc; //!< Quantidade de argumentos passados por linha de comando.
		std::vector<std::string> m_argv; //!< Lista de argumentos passados por linha de comando.
		
		std::string m_line; //<! String para armazenar uma linha lida do arquivo de entrada.
		int m_height; //<! Altura da tabela de celulas.
		int m_width; //<! Largura da tabela de células.
		char m_alive; //<! Caractere que representa uma célula viva.

		int m_currentGeneration = 1; //<! Geração atual.


		std::vector<life::Cell> cells; //!< Lista de células da simulação.
		std::vector<life::Coordenada> liveCells; //<! Lista de coordenadas das células vivas da simulação.
		std::vector<life::Cell> cellsCopy; //<! Copia do liveCells.

		std::string m_imagesDirectory = "none"; //<! Diretorio na qual as imagens da simulação serão armazenadas.
		std::string m_outfileName = "none";
		int m_maxGen = -1; //<! Quantidade de gerações que serão executadas. Padrão = -1.
		int m_fps = 2; //<! Numero de fps das exibições das gerações. Padrão = 2.
		int m_blockSize = 5; //<! Tamanho do bloco que representará uma célula na geração. Padrão =  5.
		//life::Color m_bgkColor{255,255,255}; //<! Cor de fundo da imagem. Padrão = Branco.
		std::string m_backgroundColor = "green";
		std::string m_aliveColor = "red";

		std::vector<std::string> m_generationData; //<! Armazenamento da lista de células vivas de todas as gerações.

		/* Metodos privados */

		/*
		 * Imprime a matriz de células na saida padrão.
		*/
		void print();

		void print_file();
		/*
		 * Carrega as configurações passadas no arquivo.
		 * @param arquivo, arquivo de configuração.
		*/
		void carregar_configuracoes(std::fstream &config);
		/*
		 * Valida os argumentos passados pela linha de comando, retornando falso caso não sejam validos ou insuficientes.
		 * @return true caso todos os argumentos sejam validados e false caso contrario.
		*/
		bool validar_argumentos(void);

		/*
		 * Verifica quantos vizinhos a célula tem.
		 * @param i, Coluna onde está a célula.
		 * @param j, linha onde está a célula.
		 * @return O numero de vizinhos da célula.
		*/
		short check_neighbors(int i, int j);
		/*
		 * Atualiza a lista de células vivas.
		 * @param lista de células.
		*/
		void update_liveCells(std::vector<life::Cell> &c);
		/*
		 * Salva a lista de células vivas em uma lista de gerações. As gerações são adicionadas de acordo com sua ordem.
		*/
		void save_generations();
		/*
		 * Processa a simulação de acordo com as regras do jogo da vida.
		*/
		void process_simulation();
		/*
		 * Verifica se a geração é estavél. Ou seja, existe outra geração no passado que foi igual a ela.
		 * @return true caso sejá estavél e false caso contrario.
		*/
		bool is_stable();
		/*
		 * Verifica se a geração é extinta. Ou seja, não existe nenhuma célula viva.
		 * @return true caso seja extinta e false caso contrario.
		*/
		bool is_extinguished();

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
		/*
		 * Valida os argumentos passados na linha de comando e finaliza a simulação caso eles sejam invalidos.
		 * @return true caso todos os asgumentos sejam validados e false caso contrario.
		*/
		bool start(void);
		
		/*
		 * Verifica se a simulação deve finalizar.
		 * @return true caso a simulação seja finalizada e false caso contrario.
		*/
		bool end_simulation();


};


#endif