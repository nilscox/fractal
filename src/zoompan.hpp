#ifndef ZOOMPAN_HPP_
#define ZOOMPAN_HPP_

#include "event.hpp"
#include "vector2.hpp"

class ZoomPan
{
public:
  ZoomPan(double zoomSpeed = 1, double panSpeed = 1);

  virtual double updateZoom(const Event& evt, double speed);
  virtual Vector2 updatePan(const Event& evt, double speed);

private:
  double _zoomSpeed;
  double _panSpeed;
};

#endif /* !ZOOMPAN_HPP_ */
