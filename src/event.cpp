#include "event.hpp"

Event::Event()
{
  _quit = false;
  for (int i = 0; i < SDLK_LAST; ++i)
    _key[i] = false;
  for (int i = 0; i < 8; ++i)
    _mbtn[i] = false;
}

bool Event::quit() const
{
  return _quit;
}

bool Event::key(int k) const
{
  if (k < 0 || k >= SDLK_LAST)
    throw std::range_error("Event::key: index out of bounds");
  return _key[k];
}

bool Event::btn(int b) const
{
  if (b < 0 || b >= 8)
    throw std::range_error("Event::btn: index out of bounds");
  return _mbtn[b];
}

Vector2 Event::mouse() const
{
  return _mpos;
}

void Event::update()
{
  SDL_Event e;

  _mbtn[SDL_BUTTON_WHEELUP] = false;
  _mbtn[SDL_BUTTON_WHEELDOWN] = false;

  while(SDL_PollEvent(&e))
  {
    switch (e.type)
    {
    case SDL_QUIT:
      _quit = true;
      break;

    case SDL_KEYDOWN:
      _key[e.key.keysym.sym] = true;
      break;

    case SDL_KEYUP:
      _key[e.key.keysym.sym] = false;
      break;

    case SDL_MOUSEBUTTONDOWN:
      _mbtn[e.button.button] = true;
      break;

    case SDL_MOUSEBUTTONUP:
      if (e.button.button != SDL_BUTTON_WHEELUP &&
          e.button.button != SDL_BUTTON_WHEELDOWN)
      _mbtn[e.button.button] = false;
      break;

    case SDL_MOUSEMOTION:
      _mpos.set(e.motion.x, e.motion.y);
      break;

    default:
      break;
    }
  }
}
