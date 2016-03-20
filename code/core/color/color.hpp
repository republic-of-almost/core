#ifndef COLOR_INCLUDED_FA0621D5_83C0_4765_8B7C_E44F07C3EC2F
#define COLOR_INCLUDED_FA0621D5_83C0_4765_8B7C_E44F07C3EC2F


#include <stdint.h>


namespace Core {


/*!
  Represents a generic color.
  This is an immutable object.
  
  We represent color as.
  0xAARRGGBB
*/
class Color
{
public:


  explicit constexpr
  Color(const uint32_t hex_value = 0xFFFFFFFF)
  : m_color(hex_value)
  {
  }
  
  
  explicit constexpr
  Color(const float r, const float g, const float b, const float a = 1.f)
  : m_color((uint32_t)((static_cast<uint32_t>(r * 255) << 24) |
                       (static_cast<uint32_t>(g * 255) << 16) |
                       (static_cast<uint32_t>(b * 255) << 8) |
                       (static_cast<uint32_t>(a * 255) << 0)))
  {
  }
  
  
  uint32_t                      get_color() const { return m_color; }
  float                         get_red() const;
  float                         get_green() const;
  float                         get_blue() const;
  float                         get_alpha() const;
  
  /*
    Predefined colors
  */
  constexpr static Color        white()   { return Color(0xFFFFFFFF); }
  constexpr static Color        black()   { return Color(0xFF000000); }
  constexpr static Color        red()     { return Color(0xFFFF0000); }
  constexpr static Color        green()   { return Color(0xFF00FF00); }
  constexpr static Color        blue()    { return Color(0xFF0000FF); }
  constexpr static Color        yellow()  { return Color(0xFFFFFF00); }
  constexpr static Color        magenta() { return Color(0xFFFF00FF); }
  constexpr static Color        cyan()    { return Color(0xFF00FFFF); }
  
private:

  const uint32_t        m_color;

};


} // ns


#endif // inc guard