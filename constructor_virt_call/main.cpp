#include <iostream>


class Base
{
public:
  Base()
  {
    this->init();
  }

  virtual void init() { std::cout << "Base init\n"; }
};

class Inherited: public Base
{
public:
  virtual void init() override { std::cout << "Init overrided\n"; }
};


int main(int /*argc*/, char* /*argv*/[])
{
  Base a;
  Inherited b;
}
