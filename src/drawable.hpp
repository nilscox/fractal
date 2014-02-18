#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <SDL/SDL.h>

class Drawable
{
public:
  virtual void draw(SDL_Surface* dst) const = 0;
};

#endif /* !DRAWABLE_HPP_ */
