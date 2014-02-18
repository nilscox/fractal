#ifndef FRACTAL_HPP_
#define FRACTAL_HPP_

#include <stdexcept>

#include "canvas.hpp"
#include "view.hpp"
#include "zoompan.hpp"
#include "event.hpp"
#include "palette.hpp"

class Fractal : public Canvas, public View, public ZoomPan
{
public:
  Fractal(int w, int h);

  void redrawNeeded();
  virtual void update(const Event& evt, double speed);

  virtual void compute() = 0;

protected:
  bool _redrawNeeded;
  int _maxIter;
  bool _smooth;
  Palette _palette;
};

#endif /* !FRACTAL_HPP_ */
