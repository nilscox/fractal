#include "mandelbrot.hpp"

Mandelbrot::Mandelbrot(int w, int h)
  : Fractal(w, h), ZoomPan(0.05, 5)
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
  Fractal::update();

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

  updateZoom(evt, speed);
  updatePan(evt, speed);
  updateIterations(evt, speed);
}

double Mandelbrot::updateZoom(const Event& evt, double speed)
{
  double z = ZoomPan::updateZoom(evt, speed);
  if (z)
  {
    zoom(z, evt.mouse() / getZoom() + getPosition());
    redrawNeeded();
  }

  return z;
}

Vector2 Mandelbrot::updatePan(const Event& evt, double speed)
{
  Vector2 pan = ZoomPan::updatePan(evt, speed/getZoom());
  if (pan != Vector2::ZERO)
  {
    move(pan);
    redrawNeeded();
  }

  return pan;
}

int Mandelbrot::updateIterations(const Event& evt, double speed)
{
  int i = 0;
  if (evt.key(SDLK_KP_PLUS))
    ++i;
  if (evt.key(SDLK_KP_MINUS))
    --i;

  i *= speed;
  if (i)
    _maxIter += i;

  return i;
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
