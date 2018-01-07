#include "MaintenanceStorage.hpp"

#include <typeinfo>

class A {
public:
  void SerializeToOstream(std::ostream *os) { *os << "A"; }

private:
};

class B {
public:
  void SerializeToOstream(std::ostream *os) { *os << "B"; }

private:
};

int main(int argc, char *argv[])
{
  lidia::MaintenanceStorage<20, A, B> storage;

  A a;
  B b;

  storage.update(a);
  storage.update(b);

  return 0;
}
