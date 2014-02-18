#include "program.hpp"

Program::Program()
  : _win(NULL)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("Program::init: Cannot start SDL");
}

Program::~Program()
{
  if (_win)
      delete _win;

  SDL_Quit();
}

void Program::mainLoop()
{
  if (!_win)
    return;

  Event e;
  while (!e.quit())
  {
    e.update();
    update(e);
    draw();
    _win->render();
  }
}
