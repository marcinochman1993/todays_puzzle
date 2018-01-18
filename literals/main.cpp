#include <iostream>
#include <complex>


// user defined literal
constexpr std::complex<long double> operator ""_j(long double imag)
{
    return std::complex<long double>(0, imag);
}


int main(int argc, char *argv[])
{
    auto j = 1.2_j;
    auto binary = 0b111; // binary literal
    auto separated = 1'000'000; // separated with '

    std::cout << "std::complex: " << j << '\n'
              << "binary: " << binary << '\n'
              << "separated: " << separated << std::endl;
    return 0;
}
