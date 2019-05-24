#include <iostream>
#include <vector>
#include <cstring>

#include "common.h"
#include "lodepng.h"
/// Representa um conjunto de pixel a modo de formar uma imagem.
class Canvas{

    private:
        using byte = unsigned char; //<! typedef unsigned char byte;
        static constexpr int depth=4; //<! Profundidade. Quantidade de dados pra cada pixel. R, G, B e transparencia.
        size_t m_width, m_height; //<! Dimensões.
        short m_blockSize; //<! Tamanho do bloco que representara um unico pixel.
        byte *m_pixels; //<! Conjunto de pixels.

    public:
        /*!
         * Construtor padrão.
         * @param width_ Largura da matriz de pixels.
         * @param height_ Altura da matriz de pixels.
         * @param block_s Tamanho do bloco que representará um pixel.
         * @param color Cor que todos os pixels terão.
        */
        Canvas(size_t width_, size_t height_ , short block_s, const std::string &color) {
        	m_width = width_;
        	m_height = height_;
        	m_blockSize = block_s;
            m_pixels = new byte[(m_width * m_blockSize) * (m_height * m_blockSize) * depth];
            preencher_pixels(color); // Preenche todos os pixels com a cor definida na inicialização do Canvas.
        }
        /*!
         * Destrutor.
        */
        ~Canvas() {
            delete [] m_pixels;
        }
        /*!
         * Preenche todas os pixels do canvas com uma unica cor.
         * @param color Cor que irá preencher todos os pixels.
        */
        void preencher_pixels(const std::string &color) {
            size_t i = 0;
            int R = (int)life::color_pallet[color].channels[0];
            int G = (int)life::color_pallet[color].channels[1]; 
            int B = (int)life::color_pallet[color].channels[2];
            // Definir cor personalizada.
            while(i < (m_width * m_blockSize) * (m_height * m_blockSize) * depth) {
                m_pixels[i] = R;
                m_pixels[i+1] = G;
                m_pixels[i+2] = B;
                m_pixels[i+3] = 255; // Nunca muda a transparencia.
                i+=4;
            }
        }
        /*!
         * @return A largura do canvas.
        */
        size_t get_width(void) const { 
        	return m_width * m_blockSize;
        }
        /*!
         * @return A altura do canvas.
        */
        size_t get_height(void) const { 
			return m_height * m_blockSize; 
		}
        /*!
         * Define a cor de um determinado pixel para uma determinada cor.
         * @param x Coordenada x do pixel.
         * @param y Coordenada y do pixel.
         * @param color Cor a qual o pixel será pintado.
        */
        void set_pixel( int x, int y, const std::string &color) {
            int R = (int)life::color_pallet[color].channels[0];
            int G = (int)life::color_pallet[color].channels[1];
            int B = (int)life::color_pallet[color].channels[2];
        	int inicio; //Indicara onde se inicia o bloco.
        	inicio = (m_width * x * 4 * m_blockSize * m_blockSize) + (y * 4 * m_blockSize);
        	short block_heigth = m_blockSize;  //Altura do bloco, para realizarmos o preenchimento de block_heigth linhas.

        	while(block_heigth > 0) {
        		for(int i = inicio; i < inicio + (4 * m_blockSize); i+= 4) {
	        		m_pixels[i] = R; 
		            m_pixels[i+1] = G;
		            m_pixels[i+2] = B;
        		}
        		inicio = inicio + (m_blockSize * 4) * m_width;
        		block_heigth--;
        	}
        }
        /*!
         * @return A lista de pixels do canvas.
        */
        const byte *pixels(void) const {
            return m_pixels;
        }
};


