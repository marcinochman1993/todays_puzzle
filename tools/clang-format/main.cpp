
//example of messy code
// g++ main.cpp  -std=c++11
// clang-format --style=file main.cpp

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>


namespace lidia
{
  namespace steering
  {
    struct CarState
    {
      float steeringWheelAngle;
      float wheelsAngle;
      float speed;
      float throttle;
      int rpm;
      int breaks;
      float accelerationX;
           float accelerationY;
      float accelerationZ;
      bool driverDoorOpened; //                            some comment
      bool passagerDoorOpened;



      bool rearDoorsOpened;
      bool trunkOpened;
      bool hoodOpened;
      int temp;
      int engineTemp;
      bool handbrakeActive;
      int fuelLevel;
      bool lowBeamActive;
      bool highBeamActive;
      bool hornActive;
      bool warningLightsActive;
      bool turnsignalActive;





    };




  }

  int foo(int x, int y, int z, int a, int b, int c)
  {
    std::vector<int> vec = {1,2,3,4,5,6,   7};



    return vec
      .size();
  }

  template <typename T, typename U>
  struct Pair
  {
    T first;
    T second;
  };

  template <typename T, typename U>
  Pair<T,U> createPair(T&& first, U&& second)
  {
    return
      Pair<T, U>{first, second};
  }

}


int main()
{
  auto pair =
    lidia::createPair(10, 20);

  return 0;
}
