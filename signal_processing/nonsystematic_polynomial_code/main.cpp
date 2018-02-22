// g++ main.cpp -std=c++14
#include <iostream>
#include <bitset>
#include <vector>

template <int N, int K>
using Matrix = std::vector<std::bitset<N>>;

template <int N, int K>
Matrix<N, K> matrixGenerator(std::bitset<N - K + 1> generator,
                             std::bitset<K> data)
{
  Matrix<N, K> result;
  result.reserve(K);

  for(int i = K - 1; i >= 0; i--)
  {
    std::bitset<N> matrixGenRow{generator.to_ulong()};

    matrixGenRow <<= i;

    result.push_back(matrixGenRow);
  }

  return result;
}

template <int N, int K>
std::bitset<N> nonsystematicPolyCode(std::bitset<N - K + 1> generator, std::bitset<K> data)
{
  std::bitset<N> result;

  const auto gMatrix = matrixGenerator<N, K>(generator, data);

  for(int k = 0; k < K; k++)
  {
    std::bitset<N> tempResult;

    for(int n = 0; n < N; n++)
    {
      tempResult[n] = gMatrix[k][N - n - 1] && data[k];
    }

    result ^= tempResult;
  }

  return result;
}

int main()
{
  const auto generator = std::bitset<2>(0b11);
  const auto data= std::bitset<5>(0b01011);

  std::cout << "g(x) = " << generator << std::endl;;
  std::cout << "u(x) = " << data << std::endl;

  std::cout << nonsystematicPolyCode<6, 5>(generator, data) << std::endl;
}
