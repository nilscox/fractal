#ifndef MANDELBROT_HPP_
#define MANDELBROT_HPP_

#include <cmath>

#include "fractal.hpp"
#include "zoompan.hpp"
#include "event.hpp"

class Mandelbrot : public Fractal, public ZoomPan
{
public:
  Mandelbrot(int w, int h);
  virtual ~Mandelbrot();

  virtual double updateZoom(const Event& evt, double speed);
  virtual Vector2 updatePan(const Event& evt, double speed);
  virtual int updateIterations(const Event& evt, double speed);

  using Fractal::update;
  virtual void update(const Event& evt);

  virtual void compute();

protected:
  double _bailout;
  double _speed;
};

#endif /* !MANDELBROT_HPP_ */
