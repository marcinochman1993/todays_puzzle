// g++ main.cpp -std=c++17 -o prototype
#include <iostream>
#include <memory>
#include <vector>

struct Point
{
  int x;
  int y;
  int z;
};

class IObject
{
public:
  virtual void draw() { }
  virtual void move(const Point& /*p*/) { }

  virtual IObject* clone() = 0;
};

using MeshPoints = std::shared_ptr<std::vector<Point>>;

class House: public IObject
{
public:
  House* clone() override { std::cout << "Cloning House;\n"; return new House{*this}; };
private:
  // implementation specific

  MeshPoints m_points;
};

class Human: public IObject
{
public:
  Human* clone() override { std::cout << "Cloning Human;\n"; return new Human{*this}; };

private:
  // implementation specific

  MeshPoints m_points;
};


int main(int, char* argv[])
{
  std::vector<std::unique_ptr<IObject>> vec;

  auto humanOriginal = std::make_unique<Human>();
  auto houseOriginal = std::make_unique<House>();

  // loading meshes for humanOriginal and houseOriginal

  for(int humanId = 0; humanId < 5; ++humanId)
    vec.push_back(std::unique_ptr<IObject>{humanOriginal->clone()});

  for(int houseId = 0; houseId < 5; ++houseId)
    vec.push_back(std::unique_ptr<IObject>{houseOriginal->clone()});

}
