#include "canvas.hpp"

Canvas::Canvas(int w, int h)
  : _w(w), _h(h)
{
  _src = SDL_CreateRGBSurface(SDL_HWSURFACE, _w, _h, 32, 0, 0, 0, 0);
}

Canvas::~Canvas()
{
  SDL_FreeSurface(_src);
}

void Canvas::setPixel(int x, int y, const Color& c)
{
  if (x < 0 || x >= _w || y < 0 || y >= _h)
    throw std::range_error("Canvas::setPixel: out of bounds");
  unsafe_setPixel(x, y, c);
}

void Canvas::unsafe_setPixel(int x, int y, const Color& c)
{
  *((Uint32*)(_src->pixels) + x + y * _src->w) = c.toUint32(_src->format);
}

Color Canvas::getPixel(int x, int y) const
{
  if (x < 0 || x >= _w || y < 0 || y >= _h)
    throw std::range_error("Canvas::getPixel: out of bounds");
  return unsafe_getPixel(x, y);
}

Color Canvas::unsafe_getPixel(int x, int y) const
{
  (void)x;
  (void)y;
  return Color::Black;
}

int Canvas::getWidth() const
{
  return _w;
}

int Canvas::getHeight() const
{
  return _h;
}

void Canvas::saveToFile(const std::string& filename) const
{
  SDL_SaveBMP(_src, filename.c_str());
}

void Canvas::draw(SDL_Surface* dst) const
{
  SDL_BlitSurface(_src, NULL, dst, NULL);
}
