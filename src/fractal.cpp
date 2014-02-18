#include "fractal.hpp"

Fractal::Fractal(int w, int h)
  : Canvas(w, h), _palette(Color::White)
{
  _redrawNeeded = true;
  _smooth = true;
  _maxIter = 60;
}

void Fractal::redrawNeeded()
{
  _redrawNeeded = true;
}

void Fractal::update()
{
  if (_redrawNeeded)
  {
    compute();
    _redrawNeeded = false;
  }
}
