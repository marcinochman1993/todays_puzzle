#include <iostream>

// Variadic templates and recursion - C++11
template <typename T>
T sum(T a)
{
    return a;
}

template <typename T, typename ... Args>
T sum(T a, Args... args)
{
    return a + sum(args...);
}

// Sum using fold expression - C++17
template <typename T, typename ...Args>
T sum_fold_expression(Args... args)
{
    return  (... + args);
}

int main(int argc, char *argv[])
{
    std::cout << "Old way: " << sum(10, 11, 12) << std::endl;
    std::cout << "Fold expression: " << sum_fold_expression<int>(10, 11, 12) << std::endl;;

    return 0;
}
