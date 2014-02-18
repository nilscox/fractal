#ifndef FRACTAL_HPP_
#define FRACTAL_HPP_

#include <stdexcept>

#include "canvas.hpp"
#include "palette.hpp"
#include "view.hpp"

class Fractal : public Canvas, public View
{
public:
  Fractal(int w, int h);

  void redrawNeeded();
  virtual void update();

  virtual void compute() = 0;

protected:
  bool _redrawNeeded;
  int _maxIter;
  bool _smooth;
  Palette _palette;
};

#endif /* !FRACTAL_HPP_ */
