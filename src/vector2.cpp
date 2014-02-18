#include "vector2.hpp"

Vector2 Vector2::ZERO = Vector2(0, 0);
Vector2 Vector2::UNITX = Vector2(1, 0);
Vector2 Vector2::UNITY = Vector2(0, 1);

Vector2::Vector2(double _x, double _y)
{
  set(_x, _y);
}

double Vector2::length() const
{
  return sqrt(lengthSq());
}

double Vector2::lengthSq() const
{
  return x*x + y*y;
}

void Vector2::set(double _x, double _y)
{
  x = _x;
  y = _y;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
  x += v.x;
  y += v.y;

  return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
  x -= v.x;
  y -= v.y;

  return *this;
}

Vector2& Vector2::operator*=(double k)
{
  x *= k;
  y *= k;

  return *this;
}

Vector2& Vector2::operator/=(double k)
{
  x /= k;
  y /= k;

  return *this;
}

bool Vector2::operator==(const Vector2& v)
{
  return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2& v)
{
  return x != v.x || y != v.y;
}

std::ostream& operator<<(std::ostream& strm, const Vector2& v)
{
  strm << "Vector(" << v.x << ';' << v.y << ")";
  return strm;
}

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
  Vector2 v(v1);
  v += v2;
  return v;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
  Vector2 v(v1);
  v -= v2;
  return v;
}

Vector2 operator*(const Vector2& v1, double k)
{
  Vector2 v(v1);
  v *= k;
  return v;
}

Vector2 operator/(const Vector2& v1, double k)
{
  Vector2 v(v1);
  v /= k;
  return v;
}
