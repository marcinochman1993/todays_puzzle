#include <iostream>
#include <string>


class B
{
public:
    B(int )
    {
        throw "Not implemented yet";
    }
};

class A
{
public:
    A()
        try: b(1)
        {
            // constructor body
        }
    catch(...)
        {
            std::cerr << "Eexception in constructor" << std::endl;
        }
private:
    B b;
};


int main(int argc, char *argv[])
{
    try
    {
        A a;
    }
    catch(...)
    {
        std::cerr << "Exception in main" << std::endl;
    }

    return 0;
}
