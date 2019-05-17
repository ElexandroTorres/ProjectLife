
#include <iostream>
#include <vector>
#include <cstring>

#include "common.h"
#include "lodepng.h"

namespace life {

    class Canvas{
        private:
            using byte = unsigned char;//typedef unsigned char byte;
            static constexpr int depth=4;
            size_t m_width, m_height;
            short block_size;
            byte *m_pixels;
            //Preenche todos os pixels de uma só cor, assim defindo a cor de fundo.
            void preencher_pixels() {
                int i = 0;
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
            /*
             * Construtor da classe canvas.
             * @param width_, largura da imagem.
             * @param height_, altura da imagem.
             * @param block_s, o tamanho do bloco que ira representar um pixel.
            */
            Canvas(size_t width_, size_t height_ , short block_s) {
                m_width = width_;
                m_height = height_;
                block_size = block_s;

                m_pixels = new byte[(m_width * block_size) * (m_height * block_size) * depth];
                preencher_pixels(); //Preenche todos os pixels com uma determinada cor....mudar nome pra preencher background.
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
            /*
             * Pinta um conjunto de pixels(representando um pixel na imagem) com uma determinada cor.
             * @param x, coordenada x do pixel.
             * @param y, coordenada y do pixel.
             * @param color, a cor que será usada para preencher o pixel. 
            */
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
                    inicio = inicio + (block_size * 4) * m_width;    //(block_size*4 + block_size*4)
                    block_heigth--;
                }

            }

            const byte *pixels(void) const {
                return m_pixels;
            }
};
// Example 1
// Encode from raw pixels to disk with a single function call
// The image argument has width * height RGBA pixels or width * height * 4 bytes
void encode_png(const char* filename, const unsigned char * image, unsigned width, unsigned height) {
    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}    
}




int main() {
    Canvas img( 50, 50, 30);
    //largura x altura...
    //pintar todos os pixels, teste.
    for(int i = 0; i < 50; i++) {
    	//for(int j = 0; j < 50; j++) {
    		img.set_pixel( i,1, life::RED );		
    	//}
    }
    //img.set_pixel( 0,0, life::RED );

    encode_png("teste.png", img.pixels(), (unsigned) img.get_width(), (unsigned) img.get_height() );
}
