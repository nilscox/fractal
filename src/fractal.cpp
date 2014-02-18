#include "fractal.hpp"

Fractal::Fractal(int w, int h)
  : Canvas(w, h), ZoomPan(0.05, 5), _palette(Color::White)
{
  _redrawNeeded = true;
  _smooth = true;
  _maxIter = 60;
}

void Fractal::redrawNeeded()
{
  _redrawNeeded = true;
}

void Fractal::update(const Event& evt, double speed)
{
  double z = updateZoom(evt, speed);
  if (z != 1)
  {
    zoom(z, evt.mouse() / getZoom() + getPosition());
    redrawNeeded();
  }

  Vector2 pan = updatePan(evt, speed/getZoom());
  if (pan != Vector2::ZERO)
  {
    move(pan);
    redrawNeeded();
  }

  int i = 0;
  if (evt.key(SDLK_KP_PLUS))
    ++i;
  if (evt.key(SDLK_KP_MINUS))
    --i;

  i *= speed;
  if (i)
  {
    _maxIter += i;
    redrawNeeded();
  }

  if (_redrawNeeded)
  {
    compute();
    _redrawNeeded = false;
  }
}
