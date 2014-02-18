#ifndef PALETTE_HPP_
#define PALETTE_HPP_

#include <stdexcept>
#include <map>

#include "color.hpp"

class Palette
{
public:
  Palette(const Color& def);

  void insert(double pos, const Color& c);
  Color operator[](double x) const;

private:
  std::map<double, Color> _map;
};

#endif /* !PALETTE_HPP_ */
