#include "palette.hpp"
#include <iostream>

Palette::Palette(const Color& def)
{
  _map.insert(std::pair<double, Color>(0, def));
  _map.insert(std::pair<double, Color>(1, def));
}

void Palette::insert(double pos, const Color& c)
{
  pos = pos < 0 ? 0 : (pos > 1 ? 1 : pos);

  _map.erase(pos);
  _map.insert(std::pair<double, Color>(pos, c));
}

Color Palette::operator[](double x) const
{
  x = x < 0 ? 0 : (x > 1 ? 1 : x);

  std::map<double, Color>::const_iterator prev, next;

  prev = _map.upper_bound(x);
  next = prev--;

  x = (x - prev->first) / (next->first - prev->first);

  double r = prev->second.getRed() * (1 - x) + next->second.getRed() * x;
  double g = prev->second.getGreen() * (1 - x) + next->second.getGreen() * x;
  double b = prev->second.getBlue() * (1 - x) + next->second.getBlue() * x;

  return Color(r, g, b);
}
