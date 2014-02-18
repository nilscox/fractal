#include "mandelbrot.hpp"

Mandelbrot::Mandelbrot(int w, int h)
  : Fractal(w, h)
{
  setPosition(Vector2(-2.1, -1.2));
  setZoom(100);

  _palette.insert(0, Color::Black);
  _palette.insert(0.1, Color::Red);
  _palette.insert(0.2, Color::Green);
  _palette.insert(0.3, Color::Blue);

  _bailout = 4;
  _speed = 1;
}

Mandelbrot::~Mandelbrot()
{

}

void Mandelbrot::update(const Event& evt)
{
  bool shift = evt.key(SDLK_LSHIFT) || evt.key(SDLK_RSHIFT);
  bool ctrl = evt.key(SDLK_LCTRL) || evt.key(SDLK_RCTRL);

  double speed = _speed;
  if (ctrl)
    speed *= 2;
  if (shift)
    speed /= 2;

  if (evt.key(SDLK_r))
  {
    reset();
    setPosition(Vector2(-2.1, -1.2));
    setZoom(100);
  }

  if (ctrl && evt.key(SDLK_s))
    saveToFile("fractal.bmp");

  Fractal::update(evt, speed);
}

void Mandelbrot::compute()
{
  double log2 = log(2);

  for (int i = 0; i < getWidth(); ++i)
  {
    for (int j = 0; j < getHeight(); ++j)
    {
      Vector2 c = Vector2(i, j) / getZoom() + getPosition();
      Vector2 z = Vector2::ZERO;
      double n = 0;

      while (z.lengthSq() < _bailout && n < _maxIter)
      {
        double tmp = z.x;
        z.x = z.x * z.x - z.y * z.y + c.x;
        z.y = 2 * tmp * z.y + c.y;
        ++n;
      }

      if (_smooth && n < _maxIter)
        n += 1 - log(log(z.length()))/log2;

      setPixel(i, j, n == _maxIter ? Color::Black : _palette[n/_maxIter]);
    }
  }
}
