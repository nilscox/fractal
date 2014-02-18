#include "color.hpp"

Color Color::Black = Color(0,     0,   0);
Color Color::White = Color(255, 255, 255);
Color Color::Red   = Color(255,   0,   0);
Color Color::Green = Color(  0, 255,   0);
Color Color::Blue  = Color(  0,   0, 255);

Color::Color(double r, double g, double b)
{
  set(r, g, b);
}

Color::Color(Uint32 c, SDL_PixelFormat* fmt)
{
  set(c, fmt);
}

void Color::set(Uint32 c, SDL_PixelFormat* fmt)
{
  SDL_GetRGB(c, fmt, (Uint8*)&_r, (Uint8*)&_g, (Uint8*)&_b);

  _r /= 255.f;
  _g /= 255.f;
  _b /= 255.f;
}

void Color::set(double r, double g, double b)
{
  _r = r < 0 ? 0 : (r > 1 ? 1 : r);
  _g = g < 0 ? 0 : (g > 1 ? 1 : g);
  _b = b < 0 ? 0 : (b > 1 ? 1 : b);
}

double Color::getRed() const
{
  return _r;
}

double Color::getGreen() const
{
  return _g;
}

double Color::getBlue() const
{
  return _b;
}

Uint32 Color::toUint32(SDL_PixelFormat* fmt) const
{
  return SDL_MapRGB(fmt, _r * 255, _g * 255, _b * 255);
}
