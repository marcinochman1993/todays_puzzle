#include <iostream>

// no RVO: g++ --std=c++11 main.cpp -o rvo -fno-elide-constructors
//    RVO: g++ --std=c++11 main.cpp -o rvo

class A
{
public:
    A() { std::cout << "A::A()\n"; }
    A(const A&) { std::cout << "A::A(const A&)\n"; }
    ~A() { std::cout << "A::~A()\n"; }

private:
    int tab[1000000];
};

A foo()
{
    return A{};
}


int main(int argc, char *argv[])
{
    A a = foo();
    return 0;
}
