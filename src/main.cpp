#include <string>
#include <vector>
#include "program.hpp"
#include "mandelbrot.hpp"

class MyProgram : public Program
{
public:
  MyProgram();

protected:
  virtual void update(const Event& evt);
  virtual void draw();

private:
  Mandelbrot _m;
};

MyProgram::MyProgram()
  : _m(320, 240)
{
  _win = new Window(320, 240, 32, "");
  _win->setBGColor(Color::White);
}

void MyProgram::update(const Event& evt)
{
  _m.update(evt);
}

void MyProgram::draw()
{
  _win->draw(_m);
}

int main(int argc, char** argv)
{
  std::vector<std::string> args;

  for (int i = 1; i < argc; ++i)
    args.push_back(argv[i]);

  try
  {
    MyProgram p;
    p.mainLoop();
  }
  catch (const std::exception& e)
  {
    std::cout << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
