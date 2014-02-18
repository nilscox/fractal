#ifndef MANDELBROT_HPP_
#define MANDELBROT_HPP_

#include <cmath>

#include "fractal.hpp"
#include "zoompan.hpp"
#include "event.hpp"

class Mandelbrot : public Fractal
{
public:
  Mandelbrot(int w, int h);
  virtual ~Mandelbrot();

  using Fractal::update;
  virtual void update(const Event& evt);

  virtual void compute();

protected:
  double _bailout;
  double _speed;
};

#endif /* !MANDELBROT_HPP_ */
