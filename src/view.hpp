#ifndef VIEW_HPP_
#define VIEW_HPP_

#include <cmath>

#include "vector2.hpp"

class View
{
public:
  View(Vector2 pos = Vector2::ZERO);

  Vector2 getPosition() const;
  void setPosition(const Vector2& pos);

  double getRotation() const;
  void setRotation(double theta);

  double getZoom() const;
  void setZoom(double zoom);

  void move(const Vector2& pos);

  void rotate(double theta);
  void rotate(double theta, const Vector2& p);

  void zoom(double factor);
  void zoom(double factor, const Vector2& p);

  void reset();

private:
  Vector2 _pos, _def;
  double _rot;
  double _zoom;
};

#endif /* !VIEW_HPP_ */
