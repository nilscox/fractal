#include "zoompan.hpp"

ZoomPan::ZoomPan(double zoomSpeed, double panSpeed)
{
  _zoomSpeed = zoomSpeed;
  _panSpeed = panSpeed;
}

double ZoomPan::updateZoom(const Event& evt, double speed)
{
  bool alt = evt.key(SDLK_LALT) || evt.key(SDLK_RALT);
  bool space = evt.key(SDLK_SPACE);

  double z = 0;

  if (space)
    z = alt ? -1 : 1;
  else
  {
    if (evt.btn(SDL_BUTTON_WHEELUP))
      z = 1;
    else if (evt.btn(SDL_BUTTON_WHEELDOWN))
      z = -1;
  }

  return 1 + speed * z * _zoomSpeed;
}

Vector2 ZoomPan::updatePan(const Event& evt, double speed)
{
  Vector2 result;

  if (evt.key(SDLK_LEFT))
    --result.x;
  if (evt.key(SDLK_RIGHT))
    ++result.x;

  if (evt.key(SDLK_UP))
    --result.y;
  if (evt.key(SDLK_DOWN))
    ++result.y;

  return result * _panSpeed * speed;
}
