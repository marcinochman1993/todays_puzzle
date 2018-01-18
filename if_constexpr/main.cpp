#include <cmath>
#include <iomanip>
#include <iostream>
#include <type_traits>

template <typename T> const T e = 2.71828182845904523536;

template <typename RetType, typename PowerType>
RetType quickExponent(PowerType n)
{
  std::cout << "Running quickExponent\n";
  RetType x = e<RetType>;

  if (n < 0)
  {
    n = 1 / n;
    x = 1 / x;
  }

  RetType y = 1;

  while (n > 1)
  {
    bool isEven = n % 2 == 0;

    y = isEven ? y : x * y;
    x = x * x;
    n = isEven ? n / 2 : (n - 1) / 2;
  }

  return x * y;
}

template <typename RetType, typename ParamType>
RetType exponentTaylor(ParamType x)
{
  std::cout << "Running exponentTaylor\n";
  return std::exp(x);
}


// if constexpr solution
template <typename RetType, typename ParamType>
RetType exponentIfConstExpr(ParamType n)
{
  if constexpr (std::is_integral<ParamType>::value)
    quickExponent<RetType>(n);
  else
    exponentTaylor<RetType>(n);
}


// old c++ templates solution - boilerplate code
template <typename RetType, typename ParamType, bool isIntegral>
struct ExponentStruct
{
  static RetType exponentFunction(ParamType n) { return exponentTaylor<RetType>(n); }
};

template <typename RetType, typename ParamType>
struct ExponentStruct<RetType, ParamType, true>
{
  static RetType exponentFunction(ParamType n) { return quickExponent<RetType>(n);}
};

template <typename RetType, typename ParamType>
RetType exponentOldWay(ParamType n)
{
  return ExponentStruct<
      RetType, ParamType,
      std::is_integral<ParamType>::value>::exponentFunction(n);
}


int main() {

  std::cout << std::setprecision(10) << exponentOldWay<double>(10) << '\n'
            << std::setprecision(10) << exponentIfConstExpr<double>(10) << '\n'
            << std::setprecision(10) << exponentOldWay<double>(10.0) << '\n'
            << std::setprecision(10) << exponentIfConstExpr<double>(10.0) << std::endl;
}
