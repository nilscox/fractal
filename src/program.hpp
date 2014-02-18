#ifndef PROGRAM_HPP_
#define PROGRAM_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <SDL/SDL.h>

#include "window.hpp"
#include "event.hpp"

class Program
{
public:
  Program();
  virtual ~Program();

  void mainLoop();

protected:
  virtual void update(const Event& e) = 0;
  virtual void draw() = 0;

  Window* _win;
};

#endif /* !PROGRAM_HPP_ */
