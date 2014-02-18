#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <stdexcept>
#include <string>

#include "drawable.hpp"
#include "color.hpp"

class Window
{
public:
  Window(int w, int h, int bpp, const std::string& title);

  void setBGColor(const Color& color);
  Color getBGColor() const;

  void fill(const Color& c);
  void draw(const Drawable& d);
  void render();

private:
  SDL_Surface* _screen;
  Color _bgColor;

  static bool _created;
};

#endif /* !WINDOW_HPP_ */
