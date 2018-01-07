#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <algorithm>
#include <vector>

namespace lidia
{

template<typename T>
class IObserver;

template<typename T>
class SubjectBase
{
public:
  void attach(IObserver<T>* observer) { m_observers.push_back(observer); }
  void detach(IObserver<T>* observer)
  {
    m_observers.erase(
      std::remove(std::begin(m_observers), std::end(m_observers), observer),
      std::end(m_observers));
  }

protected:
  void notify(const T& data);

private:
  std::vector<IObserver<T>*> m_observers;
};

template<typename T>
class IObserver
{
public:
  virtual void update(const T& data) = 0;
};

template<typename T>
using Subject = SubjectBase<T>;

template<typename T>
void SubjectBase<T>::notify(const T& data)
{
  for(auto& observer : m_observers)
  {
    observer->update(data);
  }
}
}
#endif /* OBSERVER_HPP */
