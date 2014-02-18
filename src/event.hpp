#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <stdexcept>
#include <SDL/SDL.h>

#include "vector2.hpp"

class Event
{
 public:
  Event();

  void update();

  bool quit() const;
  bool key(int k) const;
  bool btn(int b) const;
  Vector2 mouse() const;

 private:
  bool _quit;
  bool _key[SDLK_LAST];
  bool _mbtn[8];
  Vector2 _mpos;
};

#endif /* !EVENT_HPP_ */
