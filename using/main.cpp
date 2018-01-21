// g++ -std=c++14 main.cpp -o using
#include <map>
#include <type_traits>
#include <iostream>

using namespace std;

// the same as typedef std::vector<int> IntVector
using IntStrMap = std::map<int, string>;

// can't use templates with typedef,
template <typename KeyType, typename ValueType>
using MapIterator = typename map<KeyType, ValueType>::const_iterator;

// than use MapIterator as normal template type
using IntStrMapIterator = MapIterator<int, string>;


int main(int, char *argv[])
{
  IntStrMap map = {{1, "one"}, {2, {"two"}}};
  IntStrMapIterator it = std::cbegin(map); // better use auto

  for (; it!= std::cend(map); ++it) // better use range-loop here
  {
    cout << "{" << it->first << ": " << it->second << "}\n";
  }

}
