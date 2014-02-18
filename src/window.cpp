#include "window.hpp"

bool Window::_created = false;

Window::Window(int w, int h, int bpp, const std::string& title)
  : _screen(NULL), _bgColor(Color::Black)
{
  if (!(SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO))
    throw std::runtime_error("Window::Window: SDL wasn't initialized");

  if (Window::_created)
  {
    std::string err = "Window::Window: cannot instanciate more than one window";
    throw std::runtime_error(err);
  }
  Window::_created = true;

  _screen = SDL_SetVideoMode(w, h, bpp, SDL_HWSURFACE);
  if (!_screen)
    throw std::runtime_error("Window::Window: Cannot create the window");

  system("i3-msg floating enable");
  SDL_WM_SetCaption(title.c_str(), NULL);
  fill(_bgColor);
}

void Window::setBGColor(const Color& color)
{
  _bgColor = color;
}

Color Window::getBGColor() const
{
  return _bgColor;
}

void Window::fill(const Color& c)
{
  SDL_FillRect(_screen, NULL, c.toUint32(_screen->format));
}

void Window::draw(const Drawable& d)
{
  d.draw(_screen);
}

void Window::render()
{
  SDL_Flip(_screen);
  fill(_bgColor);
}
