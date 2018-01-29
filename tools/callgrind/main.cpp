//g++ main.cpp --std=c++14 -o profiling
//valgrind --tool=callgrind ./profiling

#include <iostream>
#include <fstream>

int writeToFileNTimesStdEnd(std::ofstream& file, const std::string& text, int n)
{
  for(int line = 0; line < n; ++line)
  {
    file << text << std::endl;
  }
}

int writeToFileNTimesNewLine(std::ofstream& file, const std::string& text, int n)
{
  for(int line = 0; line < n; ++line)
  {
    file << text << std::endl;
  }
}


int main(int, char* argv[])
{
  constexpr auto TEXT = "Hello world";
  constexpr auto LINES = 5'000'000;
  std::ofstream file1{"file1.txt"}, file2{"file2.txt"};

  writeToFileNTimesStdEnd(file1, TEXT, LINES);
  writeToFileNTimesNewLine(file2, TEXT, LINES);
}
