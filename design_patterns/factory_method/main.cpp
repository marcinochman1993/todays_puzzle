#include <iostream>
#include <memory>
#include <sstream>

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
  int valueKPlus1 = calculate(k + 1),
    valueK = calculate(k);

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

  return calculate(n - 2) + calculate(n - 1);
}

std::unique_ptr<IFibonnaci> fibonnaciCreator(const std::string& name)
{
  if(name == "doubling")
    return std::unique_ptr<IFibonnaci>{new FibonnaciDoubling()};

  if(name == "recursive")
    return std::unique_ptr<IFibonnaci>{new FibonnaciRecursive()};

  return nullptr;
}


int parseN(const std::string& strN)
{
  std::istringstream iss{strN};
  int n = 0;

  iss >> n;

  return n;
}

int main(int argc, char* argv[])
{
  if(argc < 3)
  {
    std::cerr << argv[0] << " (doubling|recursive) n\n";
    return 1;
  }

  auto algorithm = fibonnaciCreator(argv[1]);

  if(algorithm != nullptr)
    std::cout << "Result: " << algorithm->calculate(parseN(argv[2]));
  else
    std::cerr << "Unsupported algorithm specified\n";

}
