#ifndef COMMON_H
#define COMMON_H

#include <cstring> 
#include <iostream>
#include <map>

namespace life {
  /// Representa uma célula do life.
  class Cell {

    private:
      bool c_alive; /*!< Estado da célula, true significa celula viva e false celula morta. */
      short c_numberOfNeighbors; /*!< Quantidade de vizinhos atuais da célula que estão vivos. */
    public:
      /*!
       * Construtor padrão, inicializando a célula como morta.
       * @param alive Booleano que define o estado da célula. Padrão = false.
      */
      Cell(bool alive = false) {
        c_alive = alive;
        c_numberOfNeighbors = 0;
      }
      /*!
       * Construtor copia.
      */
      Cell(const Cell &clone) {
            c_alive = clone.c_alive;
            c_numberOfNeighbors = clone.c_numberOfNeighbors;
      }
      /*!
      * Destrutor padrão.
      */
      ~Cell() = default;
      /*!
      * Atribui um estado para a celula.
      * @param state Booleano representado o estado da célula. True para viva e false para morta.
      */
      void set_state(bool state) {
        c_alive = state;
      }
      /*!
       * Verifica se a célula está viva.
       * @return true caso esteja viva e false caso contrario.
      */
      bool is_alive() {
        return c_alive;
      }
      /*!
       * "Mata" a célula definindo seu estado para false.
      */
      void kill() {
        c_alive = false;
      }
      /*!
       * Faz "nascer" uma célula definindo seu estado para true.
      */
      void born() {
        c_alive = true;
      }
      /*!
       * Define a quantidade de vizinhos vivos da célula.
       * @param n Numero de vizinhos vivos.
      */
      void set_neighbors(short n) {
        c_numberOfNeighbors = n;
      }
      /*!
       * Retorna o numero de vizinhos vivos da célula.
       * @return Quantidade de vizinhos vivos.
      */
      short neighbors() {
        return c_numberOfNeighbors;
      }
  };
  /// Representa a coordenada de um pixel.
  class Coordenada {
    private:
      typedef long coord_type; //!< The cell coordinate type.
      coord_type m_x; //!< Coordenada do ponto x.
      coord_type m_y; //!< Coordenada do ponto y..

    public:
      /*!
       * Cria uma coordenada.
       * @param x representa o x da coordenada. 
       * @param y representa o y da coordenada.
      */
      Coordenada(coord_type x=0, coord_type y=0) {
        m_x = x;
        m_y = y;
      }
      /// Construtor copia.
      Coordenada(const Coordenada& clone) {
        m_x = clone.m_x;
        m_y = clone.m_y;
      }
      /// Destrutor.
      ~Coordenada() = default;
      /*!
       * @return O x da coordenada solicitada.
      */
      coord_type get_x() {
        return m_x;
      }
      /*!
       * @return O y da coordenada solicitada.
      */
      coord_type get_y() {
        return m_y;
      }
      /// Sobrecarga de igualdade.
      bool operator==(const Coordenada& rhs) const {
        return m_x == rhs.m_x and m_y == rhs.m_y; 
      }
      /// Sobrecarga de diferença..
      bool operator!=( const Coordenada& rhs ) const {
        return m_x != rhs.m_x or m_y != rhs.m_y; //Caso uma seja diferente, a coordenada é diferente.
      }
       /// Decrement the point.
      Coordenada operator--() {
        --m_x; --m_y;
        return *this;
      }
      Coordenada operator--(int) {
        Coordenada temp(*this);
        m_x--; m_y--;
        return temp;
      }
       /// Stream extractor
      friend std::ostream& operator<<( std::ostream& os, const Coordenada& p) {
        os << p.m_x << " " << p.m_y;
        return os;
      }
   };
   /// Representa uma cor como um conjunto de dados representando os canais R, G e B.
   struct Color {
       //=== Alias
       typedef unsigned char color_t; //!< Type of a color channel.
       /// Identifica cada uma das 3 cores.
       enum channel_e : color_t { R=0, //!< Red channel.
                                  G=1, //!< Green channel.
                                  B=2 //!< Blue channel
       };

       //=== Members
       color_t channels[3]; //!< Armazena cada um dos 3 canais de cores.
       //=== Methods
       /// Cria uma cor.
       Color( color_t r=0, color_t g=0, color_t b=0 ) : channels{r,g,b} {/*empty*/}
       /// Construtor copia.
       Color( const Color& clone ) {
           std::memcpy( channels, clone.channels, sizeof(color_t)*3 );
       }
       /// Operador de igualdade.
       Color& operator=( const Color& rhs ) {
           if ( &rhs != this )
               std::memcpy( channels, rhs.channels, sizeof(color_t)*3 );
           return *this;
       }
       /// Operador de comparação.
       bool operator==( const Color& rhs ) {
           return not std::memcmp( channels, rhs.channels, sizeof(color_t)*3 );
       }
       friend std::ostream& operator<<( std::ostream& os, const Color& c ) {
           os << "("<< (int)c.channels[0] << "," << (int)c.channels[1] << "," << (int)c.channels[2] << ")";
           return os;
       }
   };

   // A basic color pallete.
   static const Color BLACK         = Color{0,0,0}      ; //!< Black.
   static const Color WHITE         = Color{255,255,255}; //!< White.
   static const Color DARK_GREEN    = Color{0,100,0}    ; //!< Dark green.
   static const Color GREEN         = Color{0,250,0}    ; //!< Green.
   static const Color RED           = Color{255,0,0}    ; //!< Red.
   static const Color BLUE          = Color{0,0,255}    ; //!< Blue.
   static const Color CRIMSON       = Color{220,20,60}  ; //!< Crimson (kind of red).
   static const Color LIGHT_BLUE    = Color{135,206,250}; //!< Light blue.
   static const Color LIGHT_GREY    = Color{210,210,210}; //!< Light blue.
   static const Color DEEP_SKY_BLUE = Color{0,191,255}  ; //!< Deep blue.
   static const Color DODGER_BLUE   = Color{30,144,255} ; //!< Another bluish color.
   static const Color STEEL_BLUE    = Color{70,130,180} ; //!< Yet another bluish color.
   static const Color YELLOW        = Color{255,255,0}  ; //!< Yellow.
   static const Color LIGHT_YELLOW  = Color{255,255,153}; //!< Light yellow.

   /// A color palette for later use.
   static std::map< std::string, Color > color_pallet{
       { "black",         BLACK },
       {  "white",         WHITE },
       {  "dark_green",    DARK_GREEN },
       {  "red",           RED },
       {  "green",         GREEN },
       {  "blue",          BLUE },
       {  "crimson",       CRIMSON },
       {  "light_blue",    LIGHT_BLUE },
       {  "light_grey",    LIGHT_GREY },
       {  "deep_sky_blue", DEEP_SKY_BLUE },
       {  "dodger_blue",   DODGER_BLUE },
       {  "steel_blue",    STEEL_BLUE },
       {  "yellow",        YELLOW },
       {  "light_yellow",  LIGHT_YELLOW }
   };

} // namespace

#endif // COMMON_H
