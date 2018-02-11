// g++ main.cpp Timer.cpp  -std=c++14
// g++ main.cpp Timer.cpp  -std=c++14 -O2
#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include "Timer.hpp"

template <typename T>
T fibonnaciRecursive(T n)
{
  if(n == 0)
    return 0;

  if(n <= 2)
    return 1;

  return fibonnaciRecursive(n - 2) + fibonnaciRecursive(n - 1);
}

template <typename T>
T fibonnaciDoubling(T n)
{
  if(n == 0)
    return 0;

  if(n <= 2)
    return 1;

  T k = n/2;
  T valueKPlus1 = fibonnaciDoubling(k + 1),
    valueK = fibonnaciDoubling(k);

  if(n % 2 == 0)
    return valueK*(2*valueKPlus1 - valueK);

  return valueKPlus1*valueKPlus1 + valueK*valueK;
}

class IFibonnaci
{
public:
  virtual int calculate(int n) = 0;
};

class FibonnaciDoubling: public IFibonnaci
{
public:
  int calculate(int n) override;
};

int FibonnaciDoubling::calculate(int n)
{
  if(n == 0)
    return 0;

  if(n <= 2)
    return 1;

  int k = n/2;
  int valueKPlus1 = fibonnaciDoubling(k + 1),
    valueK = fibonnaciDoubling(k);

  if(n % 2 == 0)
    return valueK*(2*valueKPlus1 - valueK);

  return valueKPlus1*valueKPlus1 + valueK*valueK;

}

class FibonnaciRecursive: public IFibonnaci
{
public:
  int calculate(int n);
};

int FibonnaciRecursive::calculate(int n)
{
  if(n == 0)
    return 0;

  if(n <= 2)
    return 1;

  return fibonnaciRecursive(n - 2) + fibonnaciRecursive(n - 1);
}

constexpr int NUM_OF_ALGORITHMS = 100000;
constexpr int NUM_OF_TESTS = 10;

using FibonnaciFunction = int(*)(int);
using PolymorphismContainer = std::vector<std::unique_ptr<IFibonnaci>>;
using FunctionContainer = std::vector<FibonnaciFunction>;


void testPolymorphism(PolymorphismContainer& polyVec, const std::vector<int>& params)
{
  Timer timer;
  std::cout << "Test Polymorphism[ms]: ";
  for(int testIdx = 0; testIdx < NUM_OF_TESTS; ++testIdx)
  {
      timer.start();

      for(int idx = 0; idx < polyVec.size(); ++idx)
        polyVec[idx]->calculate(params[idx]);

      timer.stop();

      std::cout << timer.msInterval() << ", ";
  }

}

void testFunction(FunctionContainer& funVec, const std::vector<int>& params)
{
  Timer timer;
  std::cout << "Test function[ms]: ";
  for(int testIdx = 0; testIdx < NUM_OF_TESTS; ++testIdx)
    {
      timer.start();

      for(int idx = 0; idx < funVec.size(); ++idx)
        funVec[idx](params[idx]);

      timer.stop();

      std::cout << timer.msInterval() << ", ";
    }

}


int main(int, char* argv[])
{
  PolymorphismContainer polyVec;
  FunctionContainer funVec;

  std::random_device rnd_device;
  std::mt19937 mersenne_engine(rnd_device());
  std::uniform_int_distribution<int> algDist{0, 1}, nDist{0, 20};
  std::vector<int> params(NUM_OF_ALGORITHMS);

  auto paramGenerator = [&nDist, &mersenne_engine]
  {
      return nDist(mersenne_engine);
  };

  for(int algIdx = 0; algIdx < NUM_OF_ALGORITHMS; ++algIdx)
  {
    bool isDoublingAlgorithm = algDist(mersenne_engine);

    polyVec.push_back(isDoublingAlgorithm ? std::unique_ptr<IFibonnaci>(new FibonnaciDoubling()) : std::unique_ptr<IFibonnaci>(new FibonnaciRecursive));
    funVec.push_back(isDoublingAlgorithm ? fibonnaciDoubling<int> : fibonnaciRecursive<int>);
  }

  std::generate(std::begin(params), std::end(params), paramGenerator);

  testFunction(funVec, params);
  std::cout << std::endl;
  testPolymorphism(polyVec, params);

}
