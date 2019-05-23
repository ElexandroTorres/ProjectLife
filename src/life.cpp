#include "../include/life.h"

/* Funções globais de life. */
/*
 * Valida uma string como representação de um numero.
 * @param number string que representa o número.
 * @return true caso seja um numero valido e false caso contrario.
*/
bool isValidNumber(const std::string number) {
	for(auto i = 0u; i < number.size(); i++) {
		// Caso o caractere não esteja entre 0 e 9 não será um numero valido.
		if(number[i] < '0' or number[i] > '9') {
			return false; 
		}
	}
	return true;
}
/*
 * Função para gerar a imagem.
 * @param filename, o nome da imagem.
 * @param image, tabela de pixels da imagem.
 * @param width, Largura da imagem.
 * @param height, Altura da imagem.
*/
void encode_png(const std::string filename/*const char* filename*/, const unsigned char * image, unsigned width, unsigned height) {
    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);
    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}


/* Classe Life*/

/*
 * Imprime a matriz de células na saida padrão.
*/
void Life::print() {
	std::cout << "Generation " << m_currentGeneration << ":\n";
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

void Life::print_file() {

	std::fstream outfile(m_outfileName, std::fstream::app);
	
	outfile << "Generation " << m_currentGeneration << ":\n";
	for(int j = 0; j < m_height; j++) {
		outfile << "| ";
		for(int i = 0; i < m_width; i++) {
			if(cells[i + m_width * j].is_alive()) {
				outfile << "*";
			}
			else {
				outfile << " ";	
			}
		}
		outfile << " |\n";
	}
}
/*
 * Carrega as configurações passadas no arquivo.
 * @param arquivo, arquivo de configuração.
*/
void Life::carregar_configuracoes(std::fstream &config) {
	config >> m_height; // Ler o numero de linhas(altura) da "imagem".
	config >> m_width; // Ler o numero de colunas(largura) da "imagem".
	config >> m_alive; // Ler o caractere que irá representar uma celula viva.
	
	cells.resize(m_height*m_width); // Redefine o tamanho de cells para armazenar todos as células.
	cellsCopy.resize(m_height*m_width); // Redefine o tamanho da copia.
	//Varre todo o arquivo em busca das celulas vivas e mortas e redefine seu estado.
	int row = 0;
	while(config >> m_line and row < m_height) {
		for(int column = 0; column < (int)m_line.size(); column++) {
			if(column < m_width) {
				/* Toda vez que for encontrado o caractere que representa as células vivas será definido o estado
				da céula como viva e caso o contrario como morta. */
				if(m_line[column] == m_alive) { 
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
bool Life::validar_argumentos(void) {
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

	// Varrer todos os argumentos.
	for(int i = 1; i < m_argc; i++) {
		if(m_argv[i] == "--imgdir") {
			m_imagesDirectory = m_argv[++i];
		}
		else if(m_argv[i] == "--maxgen") {
			// Verificar se o argumento seguinte é um numero valido.
			if(isValidNumber(m_argv[++i])) {
				m_maxGen = std::stoi(m_argv[i]);
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
			}
			else {
				std::cout << m_argv[i] << " it's not a valid number. Use --help to see the valid options.\n";
				return false;	
			}
		}
		else if(m_argv[i] == "--bkgcolor") {
			i++;
			m_backgroundColor = m_argv[i]; 
			// Transformar a string para letras minusculas.
			std::transform(m_backgroundColor.begin(), m_backgroundColor.end(), m_backgroundColor.begin(), ::tolower);
			/* Procura no map elementos quantos elementos estão associados a cor passada.
			Caso nenhum esteja associado significa que a cor não está disponivel */
			if(life::color_pallet.count(m_backgroundColor) == 0) {
				std::cout << "\"" << m_backgroundColor << "\"" << " is not a valid color. Use \"--help\" to see valid colors\n";
				return false;
			}

		}
		else if(m_argv[i] == "--alivecolor") {
			i++;
			m_aliveColor = m_argv[i];

			std::transform(m_aliveColor.begin(), m_aliveColor.end(), m_aliveColor.begin(), ::tolower);
			/* Procura no map elementos quantos elementos estão associados a cor passada.
			Caso nenhum esteja associado significa que a cor não está disponivel */
			if(life::color_pallet.count(m_aliveColor) == 0) {
				std::cout << "\"" << m_aliveColor << "\"" << " is not a valid color. Use \"--help\" to see valid colors\n";
				return false;
			}			
		}
		else if(m_argv[i] == "--outfile") {
			std::fstream outfile(m_argv[++i], std::fstream::out);
			//Caso não tenha sido posivel criar o arquivo.
			if(!outfile.is_open()) {
				std::cout << "Impossible to create a file in that directory\n";
				return false;
			}
			//outfile.open(m_argv[++i], std::fstream::in);
			outfile << "Game of life: \n";
			m_outfileName = m_argv[i];
			outfile.close();

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
				std::cout << "Informed input file does not exist.\n";
				return false;
			}
		}
	}
	
	return true;
}

/*
 * Verifica quantos vizinhos a célula tem.
 * @param i, Coluna onde está a célula.
 * @param j, linha onde está a célula.
 * @return O numero de vizinhos da célula.
*/
short Life::check_neighbors(int i, int j) {
	short numberOfNeighbors = 0;
	/*São verificados os casos em que os vizinhos da célula estão dentro dos limites e logo depois
	analisados os seus vizinhos validos. Caso não possua vizinho valido para alguma posição, esta posição
	não é analisada, logo não entra na contagem. */
	if(not(i-1 < 0)) {
		if(not(j-1 < 0)) {
			if(cells[(i-1) + m_width*(j-1)].is_alive()) {
				numberOfNeighbors++;
			}	
		}
		if(!(j+1 >= m_height)) {
			if(cells[(i-1) + m_width*(j+1)].is_alive()) {
				numberOfNeighbors++;
			}	
		}
		if(cells[(i-1) + m_width*j].is_alive()) {
			numberOfNeighbors++;
		}
	}

	if(!(i+1 >= m_width)) {
		if(!(j-1 < 0)) {
			if(cells[(i+1) + m_width*(j-1)].is_alive()) {
				numberOfNeighbors++;
			}	
		}
		if(!(j+1 >= m_height)) {
			if(cells[(i+1) + m_width*(j+1)].is_alive()) {
				numberOfNeighbors++;
			}	
		}
		if(cells[(i+1) + m_width*j].is_alive()) {
			numberOfNeighbors++;
		}
	}

	if(!(j-1 < 0)) {
		if(cells[i + m_width*(j-1)].is_alive()) {
			numberOfNeighbors++;
		}	
	}
	if(!(j+1 >= m_height)) {
		if(cells[i + m_width*(j+1)].is_alive()) {
			numberOfNeighbors++;
		}	
	}
	
	return numberOfNeighbors;

}
/*
 * Atualiza a lista de células vivas.
 * @param lista de células.
*/
void Life::update_liveCells(std::vector<life::Cell> &c) {
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
 * Salva a lista de células vivas em uma lista de gerações. As gerações são adicionadas de acordo com sua ordem.
*/
void Life::save_generations() {
	std::string currentGeneration = " ";
	for(auto i = 0u; i < liveCells.size(); i++) {
		currentGeneration += std::to_string(liveCells[i].get_x()) + " " + std::to_string(liveCells[i].get_y()) + " ";	
	}

	m_generationData.push_back(currentGeneration);
	
}
/*
 * Processa a simulação de acordo com as regras do jogo da vida.
*/
void Life::process_simulation() {
	
	update_liveCells(cells); // Verifica quais as células que estão vivas.
	
	save_generations(); //Adiciona as celulas vivas a uma lista de gerações.
	
	cellsCopy = cells;
	// Verifica e define quantos vizinhos cada célula tem.
	for(int j = 0; j < m_height; j++) { 
		for(int i = 0; i < m_width; i++) {
			cells[i + m_width*j].set_neighbors(check_neighbors(i, j));
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
	/* Verifica qual o modo de saida desejado para as gerações. */
	std::string filename;
	// Definir o nome do arquivo como sendo Generation + numero da geração.
	// Caso o diretorio de imagens tenha sido especificado.
	if(m_imagesDirectory != "none") {
		filename = m_imagesDirectory + "/Generation " + std::to_string(m_currentGeneration);
		Canvas img(m_width, m_height, 10, m_backgroundColor);
		// Pintar as células vivas na imagem.
		for(auto i = 0u; i < liveCells.size(); i++) {
			img.set_pixel(liveCells[i].get_x(), liveCells[i].get_y() , m_aliveColor);
		}
		// Gerar a imagem no formato png.
		encode_png(filename + ".png", img.pixels(), (unsigned) img.get_width(), (unsigned) img.get_height());	
		// Incrementa a geração atual.
	}
	// Caso um arquivo de texto de saida tenha sido especificado.
	if(m_outfileName != "none") {
		print_file();
	}
	if(m_imagesDirectory == "none") {
		print();
	}
	m_currentGeneration++;
	
}
/*
 * Verifica se a geração é estavél. Ou seja, existe outra geração no passado que foi igual a ela.
 * @return true caso sejá estavél e false caso contrario.
*/
bool Life::is_stable() {
	for(auto i = 0u; i < m_generationData.size() - 1; i++) {
		/* Verificar se a ultima geração adicionada(no caso a atual) é igual a alguma outra.
		   Caso seja, significa que a geração atual é estavel. */
		if(m_generationData[m_generationData.size()-1] == m_generationData[i]) {
			std::cout << "The last generation is stable with the generation " << i+1 << "\n";
			return true;
		}
	}
	return false;
}
/*
 * Verifica se a geração é extinta. Ou seja, não existe nenhuma célula viva.
 * @return true caso seja extinta e false caso contrario.
*/
bool Life::is_extinguished() {
	if(m_generationData[m_generationData.size()-1] == " ") {
		std::cout << "The last generation became extinct\n";
		return true;
	}
	return false;
}



bool Life::start(void) {
	//Se os argumentos não forem validados.
	if(!validar_argumentos()) {
		return false;
	}
	//caso os argumentos sejam validados exibir mensagem de boas vindas.
	return true;	
}

/*
 * Verifica se a simulação deve finalizar.
 * @return true caso a simulação seja finalizada e false caso contrario.
*/
bool Life::end_simulation() {
	/* Executa a geração de acordo com a quantidade especificada pelo usuario, caso não tenha sido especificado
	as gerações irão continuar até atigingir uma das condições de finalização: Estabilidade ou extinção. */
	if(m_maxGen != 0) {
		process_simulation(); // Processa as informações da simulação.
		// Verifica se é estavel e finaliza caso seja.
		if(is_stable()) {
			return true;
		}
		if(is_extinguished()) {
			return true;
		}
		m_maxGen--;	
		return false; //simulação não terminou.	
	}
	return true; //Simulação acabou
}




