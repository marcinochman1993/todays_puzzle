#include <iostream>

using namespace std;

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

int main()
{
  cout << "Doubling: " << fibonnaciDoubling(45) << endl;
  cout << "Slow: " << fibonnaciRecursive(45) << endl;
}
