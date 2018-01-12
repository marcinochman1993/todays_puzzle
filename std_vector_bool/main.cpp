#include <typeinfo>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    std::vector<int> vectorOfInts = {1, 2, 3};
    std::vector<bool> vectorOfBools = {true, false, true, true};

    std::cout << typeid(vectorOfInts.at(0)).name() << "\n";
    std::cout << typeid(vectorOfBools.at(0)).name() << "\n";

    return 0;
}
