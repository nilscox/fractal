#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include <cmath>
#include <iostream>

class Vector2
{
public:
  double x, y;

  Vector2(double _x = 0, double _y = 0);

  double length() const;
  double lengthSq() const;

  void set(double _x, double _y);

  Vector2& operator+=(const Vector2& v);
  Vector2& operator-=(const Vector2& v);
  Vector2& operator*=(double k);
  Vector2& operator/=(double k);

  bool operator==(const Vector2& v);
  bool operator!=(const Vector2& v);

  friend std::ostream& operator<<(std::ostream& strm, const Vector2& v);

  static Vector2 ZERO;
  static Vector2 UNITX;
  static Vector2 UNITY;
};

Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v1, double k);
Vector2 operator/(const Vector2& v1, double k);

#endif /* !VECTOR_HPP_ */
