#include "view.hpp"

View::View(Vector2 pos)
{
  _pos = pos;
  _def = pos;
  _rot = 0;
  _zoom = 1;
}

Vector2 View::getPosition() const
{
  return _pos;
}

void View::setPosition(const Vector2& pos)
{
  _pos = pos;
}

double View::getRotation() const
{
  return _rot;
}

void View::setRotation(double theta)
{
  _rot = theta;
}

double View::getZoom() const
{
  return _zoom;
}

void View::setZoom(double zoom)
{
  _zoom = zoom;
}

void View::move(const Vector2& d)
{
  _pos += d;
}

void View::rotate(double theta)
{
  _rot += theta;
}

void View::rotate(double theta, const Vector2& p)
{
  _rot += theta;
  _pos.x = p.x * cos(theta) - p.y * sin(theta);
  _pos.y = p.y * sin(theta) + p.y * cos(theta);
}

void View::zoom(double factor)
{
  _zoom *= factor;
}

void View::zoom(double factor, const Vector2& p)
{
  _zoom *= factor;

  _pos.x += (p.x - _pos.x) * (1 - 1/factor); // code smell
  _pos.y += (p.y - _pos.y) * (1 - 1/factor);
}

void View::reset()
{
  _pos = _def;
  _rot = 0;
  _zoom = 1;
}
