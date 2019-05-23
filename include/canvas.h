#include <iostream>
#include <vector>
#include <cstring>

#include "common.h"
#include "lodepng.h"

class Canvas{

    private:
        using byte = unsigned char;//typedef unsigned char byte;
        static constexpr int depth=4;
        size_t m_width, m_height;
        short block_size;
        byte *m_pixels;
        //Preenche todos os pixels de uma só cor, assim defindo a cor de fundo.
        void preencher_pixels() {
        	size_t i = 0;
        	/*
        	while(i < (m_width * block_size) * (m_height * block_size) * depth) {
        		m_pixels[i] = 255; //trocar para a cor.
        		i++;
        	}
        	*/
        	//definir cor personalizada.
        	while(i < (m_width * block_size) * (m_height * block_size) * depth) {
        		m_pixels[i] = 255;
        		m_pixels[i+1] = 0;
        		m_pixels[i+2] = 255;
        		m_pixels[i+3] = 255;
        		i+=4;
        	}
        }

    public:
        Canvas(size_t width_, size_t height_ , short block_s) {
        	m_width = width_;
        	m_height = height_;
        	block_size = block_s;
            m_pixels = new byte[(m_width * block_size) * (m_height * block_size) * depth];
            preencher_pixels();
        }
        ~Canvas() {
            delete [] m_pixels;
        }
        
        size_t get_width(void) const { 
        	return m_width * block_size;
        }

        size_t get_height(void) const { 
			return m_height * block_size; 
		}

        void set_pixel( int x, int y, const life::Color& color ) {
        	int inicio; //Indicara onde se inicia o bloco.
        	inicio = (m_width * x * 4 * block_size * block_size) + (y * 4 * block_size);
        	//int inicio = w*x*4*block_size*block_size + y*4*block_size;
        	short block_heigth = block_size;  //Altura do bloco, para realizarmos o preenchimento de block_heigth linhas.

        	while(block_heigth > 0) {
        		for(int i = inicio; i < inicio + (4 * block_size); i+= 4) {
	        		m_pixels[i] = 255; //VERMELHO...MUDAR DEPOIS
		            m_pixels[i+1] = 0;
		            m_pixels[i+2] = 0;
        		}
        		inicio = inicio + (block_size * 4) * m_width;	 //(block_size*4 + block_size*4)
        		block_heigth--;
        	}

        }

        void clear(void) {
            preencher_pixels();
        }

        void clear_pixel(int x, int y, const life::Color &color) {
            //pintar pixel com a cor do fundo.
            int inicio; //Indicara onde se inicia o bloco.
            inicio = (m_width * x * 4 * block_size * block_size) + (y * 4 * block_size);
            //int inicio = w*x*4*block_size*block_size + y*4*block_size;
            short block_heigth = block_size;  //Altura do bloco, para realizarmos o preenchimento de block_heigth linhas.

            while(block_heigth > 0) {
                for(int i = inicio; i < inicio + (4 * block_size); i+= 4) {
                    m_pixels[i] = 255; //VERMELHO...MUDAR DEPOIS
                    m_pixels[i+1] = 0;
                    m_pixels[i+2] = 255;
                }
                inicio = inicio + (block_size * 4) * m_width;    //(block_size*4 + block_size*4)
                block_heigth--;
            }            
        }

        const byte *pixels(void) const {
            return m_pixels;
        }
};


