#ifndef COMMON_H
#define COMMON_H

#include <cstring> // memset, memcpy
#include <iostream>
#include <map>

namespace life {
  /// Representa a coordenada de um pixel.
  class Coordenada {

      typedef long coord_type; //!< The cell coordinate type.
      coord_type m_x; //!< X coordinate of a point.
      coord_type m_y; //!< Y coordinate of a point.

      public:
        /// Creates a point 2d.
        Coordenada(coord_type x=0, coord_type y=0) {
          m_x = x;
          m_y = y;
        }
        /// Copy constructor
        Coordenada(const Coordenada& clone) {
          m_x = clone.m_x;
          m_y = clone.m_y;
        }

        ~Coordenada() = default;

        coord_type get_x() {
          return m_x;
        }
        coord_type get_y() {
          return m_y;
        }
        /// Equality comparison.
        bool operator==(const Coordenada& rhs) const {
          return m_x == rhs.m_x and m_y == rhs.m_y; 
        }
        /// Difference comparison.
        bool operator!=( const Coordenada& rhs ) const {
          return m_x != rhs.m_x or m_y != rhs.m_y; //Caso uma seja diferente, a coordenada é diferente.
          //return not operator==( rhs );
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


   /// Represents a Color as a RGB entity.
   struct Color {
       //=== Alias
       typedef unsigned char color_t; //!< Type of a color channel.
       /// Identifies each color channel.
       enum channel_e : color_t { R=0, //!< Red channel.
                                  G=1, //!< Green channel.
                                  B=2 //!< Blue channel
       };

       //=== Members
       color_t channels[3]; //!< Stores each of the color channels, R, G, and B.
       //=== Methods
       /// Creates a color.
       Color( color_t r=0, color_t g=0, color_t b=0 ) : channels{r,g,b} {/*empty*/}
       /// Copy constructor.
       Color( const Color& clone )
       {
           std::memcpy( channels, clone.channels, sizeof(color_t)*3 );
       }
       /// Assignment operator.
       Color& operator=( const Color& rhs )
       {
           if ( &rhs != this )
               std::memcpy( channels, rhs.channels, sizeof(color_t)*3 );
           return *this;
       }
       /// Comparison operator.
       bool operator==( const Color& rhs )
       {
           return not std::memcmp( channels, rhs.channels, sizeof(color_t)*3 );
       }
       friend std::ostream& operator<<( std::ostream& os, const Color& c )
       {
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
