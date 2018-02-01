#include <bitset>
#include <iostream>
#include <iomanip>


template <std::size_t N>
std::bitset<N+1> parityBits(const std::bitset<N>& bits)
{
  std::bitset<N+1> bitsWithParity;

  for(std::size_t bitIdx = 0; bitIdx < N; ++bitIdx)
  {
    bitsWithParity.set(bitIdx+1, bits[bitIdx]);
  }

  bitsWithParity.set(0, bits.count() % 2);

  return bitsWithParity;
}

template <std::size_t N, std::size_t K>
using LinearCodeGenerator = std::array<std::bitset<N>, K>;

template <std::size_t N, std::size_t K>
std::bitset<N+K> linearCodes(const std::bitset<N>& bits, const LinearCodeGenerator<N, K>& generator)
{
  std::bitset<N+K> linearCodeBits;

  for(std::size_t bitIdx = 0; bitIdx < N; ++bitIdx)
  {
    linearCodeBits.set(bitIdx + K, bits[bitIdx]);
  }

  for(std::size_t bitIdx = 0; bitIdx < K; ++bitIdx)
  {
    auto result = bits & generator[bitIdx];
    linearCodeBits.set(bitIdx, result.count() % 2);
  }

  return linearCodeBits;
}

int main()
{
  constexpr std::size_t BITS_COUNT = 10;
  constexpr std::size_t REDUNDANT_BITS = 3;

  using Bits = std::bitset<10>;

  Bits bits{"1110000110"};

  std::cout << std::setw(18) << "Original bits: " << std::left
            << std::setw(BITS_COUNT + REDUNDANT_BITS) << bits << "\n";

  std::cout << "Bits with parity: " << std::setw(BITS_COUNT + REDUNDANT_BITS)
            << std::left << parityBits(bits) << " <---- last bit is a parity bit\n";

  LinearCodeGenerator<BITS_COUNT, REDUNDANT_BITS> generator = {Bits{"0000000001"},
                                                               Bits{"1001000000"},
                                                               Bits{"0110000000"}};

  std::cout << std::right << std::setw(18) << "Linear code: " << std::setw(BITS_COUNT + REDUNDANT_BITS) <<
    linearCodes(bits, generator) << " <---- last 3 bits are redundant \n";
}
