#ifndef MAINTENANCESTORAGE_HPP_
#define MAINTENANCESTORAGE_HPP_

#include <boost/circular_buffer.hpp>
#include <tuple>

#include "Observer.hpp"

namespace lidia
{

template<typename T, unsigned Size>
class StorageUpdate : public IObserver<T>
{
public:
  StorageUpdate() : m_buffer(Size) {}
  void update(const T& data) override { m_buffer.push_back(data); }
  void serialize(std::ostream&);

private:
  boost::circular_buffer<T> m_buffer;
};

template<unsigned Size, typename... Args>
class MaintenanceStorage : public StorageUpdate<Args, Size>...
{
public:
  MaintenanceStorage() : StorageUpdate<Args, Size>()... {}

  // uncomment to solve compilation problem
  template<typename T>
  void update(const T& x)
  {
    StorageUpdate<T, Size>::update(x);
  }

  bool serialize(std::ostream& os)
  {
    (void)std::initializer_list<int>{ (
      StorageUpdate<Args, Size>::serialize(os), void(), 0)... };

    return true;
  }
};

template<typename T, unsigned Size>
void StorageUpdate<T, Size>::serialize(std::ostream& os)
{
  for(auto& obj: m_buffer)
    obj.SerializeToOstream(&os);
}
}
#endif /* MAINTENANCESTORAGE_HPP_ */
