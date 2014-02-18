#ifndef CANVAS_HPP_
#define CANVAS_HPP_

#include <stdexcept>
#include <iostream>
#include <string>

#include "drawable.hpp"
#include "color.hpp"

class Canvas : public Drawable
{
public:
  Canvas(int w, int h);
  virtual ~Canvas();

  void setPixel(int x, int y, const Color& c);
  void unsafe_setPixel(int x, int y, const Color& c);

  Color getPixel(int x, int y) const;
  Color unsafe_getPixel(int x, int y) const;

  int getWidth() const;
  int getHeight() const;

  virtual void saveToFile(const std::string& filename) const;
  virtual void draw(SDL_Surface* dst) const;

private:
  int _w, _h;
  SDL_Surface* _src;
};

#endif /* !CANVAS_HPP_ */
