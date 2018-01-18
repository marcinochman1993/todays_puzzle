//g++ -std=c++14 main.cpp
// required boost installed

#include <boost/iterator/zip_iterator.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace boost;

template <typename... Args>
auto makeBeginZipIterator(const Args&... args) //  remove "&" and check what happens
{
  auto t = boost::make_tuple(args.begin()...);
  return make_zip_iterator(t);
}

template <typename... Args>
auto makeEndZipIterator(const Args &... args) //remove "&" and check what happens
{
  auto t = boost::make_tuple(args.end()...);
  return make_zip_iterator(t);
}

int main()
{
  vector<string> words   = {"one", "two", "three", "four"};
  vector<int>    arabic  = {1,        2,       3,      4};
  vector<string> roman   = {"I",    "II",   "III",   "IV"};

  auto zipBegin = makeBeginZipIterator(words, arabic, roman);
  auto zipEnd = makeEndZipIterator(words, arabic, roman);

  for (auto it = zipBegin; it != zipEnd; it++)
  {
    cout << it->get<0>() << " "
         << it->get<1>() << " "
         << it->get<2>() << '\n';
  }
}
