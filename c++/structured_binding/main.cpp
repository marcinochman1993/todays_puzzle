#include <iostream>
#include <array>
#include <tuple>
#include <vector>

template <typename T, typename Container>
std::tuple<T, T> minMax(Container&& container)
{
  T minElement = *std::begin(container), maxElement = minElement;

  for(auto& element: container)
  {
    minElement = element < minElement ? element : minElement;
    maxElement = element > maxElement ? element : maxElement;
  }

  return std::make_tuple(minElement, maxElement);
}


int main(int, char* [])
{
  std::array<int, 3> table = {1, 2, 3};

  auto [minElement, maxElement] = minMax<int>(table);
  std::cout << "MinMax: [" << minElement
            << " " << maxElement << "]" << std::endl;


  auto [first, mid, last] = table;

  std::cout << "All elements: [" << first
            << " " << mid << " " << last << "]" << std::endl;

}
