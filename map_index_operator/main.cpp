#include <iostream>
#include <map>

using std::map;
using std::cout;
using std::string;

int main(int /*argc*/, char* /*argv*/[])
{
  map<int, string> dict =  {{1, "one"}, {2, "two"}, {3, "three"},
                            {4, "four"}, {5, "five"}};

  cout << "dict={\n";

  for(auto& kv: dict)
    {
      std::cout << "  (" << kv.first << ", " << kv.second << ")\n";
    }

  std::cout << "None existing field 6: \'" << dict[6] << "\'<---- WHY?!\n";

  return 0;
}
