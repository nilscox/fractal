#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <SDL/SDL.h>

class Color
{
public:
  Color(double r = 0, double g = 0, double b = 0);
  Color(Uint32 c, SDL_PixelFormat* fmt);

  void set(Uint32 c, SDL_PixelFormat* fmt);
  void set(double r, double g, double b);

  double getRed() const;
  double getGreen() const;
  double getBlue() const;

  Uint32 toUint32(SDL_PixelFormat* fmt) const;

  static Color Black;
  static Color White;
  static Color Red;
  static Color Green;
  static Color Blue;

private:
  double _r, _g, _b;
};

#endif /* !COLOR_HPP_ */
