// g++ -std=c++14 main.cpp -o perfApp
// perf stat ./perfApp
#include <iostream>
#include <vector>
#include <array>
#include <memory>

template<typename T, int Rows, int Cols>
using Matrix = std::array<std::array<T, Cols>, Rows>;

template <typename T, int Rows, int Cols>
void addRowWise(const Matrix<T, Rows, Cols>& x,
                const Matrix<T, Rows, Cols>& y,
                      Matrix<T, Rows, Cols>& result)
{
  for(int row = 0; row < Rows; ++row)
  {
    auto& xRow = x[row];
    auto& yRow = y[row];
    auto& resultRow = result[row];

    for(int col = 0; col < Cols; ++col)
      resultRow[col] = xRow[col] + yRow[col];
  }
}

template <typename T, int Rows, int Cols>
void addColumWise(const Matrix<T, Rows, Cols>& x,
                  const Matrix<T, Rows, Cols>& y,
                        Matrix<T, Rows, Cols>& result)
{
  for(int col = 0; col < Cols; ++col)
  {
    for(int row = 0; row < Rows; ++row)
      result[row][col] = x[row][col] + y[row][col];
  }
}

int main(int argc, char* argv[])
{
  constexpr int COLS = 10000, ROWS = 5000;
  using Mat = Matrix<float, ROWS, COLS>;

  std::unique_ptr<Mat> first{new Mat}, second{new Mat}, result{new Mat};

  // comment/uncomment
  // addColumWise<float, ROWS, COLS>(*first, *second, *result);
  addRowWise<float, ROWS, COLS>(*first, *second, *result);
}
