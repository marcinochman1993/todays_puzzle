#include <memory>
#include <iostream>
#include <vector>
#include <thread>

struct A
{
  int data[10000]; // decrease/increase if needed
};


int main()
{
  std::vector<std::weak_ptr<A>> vec;

  for(int idx = 0; idx < 100000; ++idx)
  {
    auto sharedPtr = std::make_shared<A>();

    vec.push_back(sharedPtr);
  }

  std::cout << "Check usage of memory in top program. Is all data deleted?.\n";
  std::this_thread::sleep_for(std::chrono::seconds(50));

  return 0;
}
