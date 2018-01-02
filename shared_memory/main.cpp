#include <array>
#include <vector>
#include <sstream>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <string>
#include <type_traits>

namespace lidia
{
template<bool currentFound,
         bool alreadyFound,
         typename T,
         typename U,
         typename... Args>
struct Offset
{
  constexpr static bool isSame = std::is_same<T, U>::value;
  constexpr static int value = Offset < isSame, isSame || alreadyFound, T,
                       Args... > ::value;
};

template<bool alreadyFound, typename T, typename U, typename... Args>
struct Offset<true, alreadyFound, T, U, Args...>
{
  constexpr static bool isSame = true;
  constexpr static int value = 0;
};

template<bool alreadyFound, typename T, typename U, typename... Args>
struct Offset<false, alreadyFound, T, U, Args...>
{

  constexpr static bool isSame = std::is_same<T, U>::value;
  constexpr static int value = sizeof(U) * !isSame + Offset < isSame,
                       isSame || alreadyFound, T, Args... > ::value;
};

template<bool alreadyFound, typename T, typename U>
struct Offset<true, alreadyFound, T, U>
{
  constexpr static bool isSame = true;
  constexpr static int value = 0;
};

template<bool found, typename T>
constexpr int assertOffset()
{
  static_assert(
    found, "No type in SharedMemoryManager given in offset template parameter");

  return 0;
}

template<bool alreadyFound, typename T, typename U>
struct Offset<false, alreadyFound, T, U>
{
  constexpr static bool isSame = std::is_same<T, U>::value;
  constexpr static int value = assertOffset < alreadyFound || isSame, T > ();
};

template<bool currentFound,
         bool alreadyFound,
         int currentIndex,
         typename T,
         typename U,
         typename... Args>
struct Index
{
  constexpr static bool isSame = std::is_same<T, U>::value;
  constexpr static int value = Index < isSame, isSame || alreadyFound,
                       currentIndex + !isSame, T, Args... > ::value;
};

template<bool alreadyFound,
         int currentIndex,
         typename T,
         typename U,
         typename... Args>
struct Index<true, alreadyFound, currentIndex, T, U, Args...>
{
  constexpr static bool isSame = true;
  constexpr static int value = currentIndex;
};

template<bool alreadyFound,
         int currentIndex,
         typename T,
         typename U,
         typename... Args>
struct Index<false, alreadyFound, currentIndex, T, U, Args...>
{
  constexpr static bool isSame = std::is_same<T, U>::value;
  constexpr static int value = Index < isSame, isSame || alreadyFound,
                       currentIndex + !isSame, T, Args... > ::value;
};

template<bool found, int currentIndex>
constexpr int assertIndex()
{
  static_assert(
    found, "No type in SharedMemoryManager given in index template parameter");

  return currentIndex;
}

template<bool alreadyFound, int currentIndex, typename T, typename U>
struct Index<false, alreadyFound, currentIndex, T, U>
{
  constexpr static bool isSame = std::is_same<T, U>::value;
  constexpr static int value = assertIndex < isSame || alreadyFound,
                       currentIndex > ();
};

template<bool alreadyFound, int currentIndex, typename T, typename U>
struct Index<true, alreadyFound, currentIndex, T, U>
{
  constexpr static bool isSame = std::is_same<T, U>::value;
  constexpr static int value = currentIndex;
};

template<typename T, typename... Args>
struct Size
{
  constexpr static int value = sizeof(T) + Size<Args...>::value;
};

template<typename T>
struct Size<T>
{
  constexpr static int value = sizeof(T);
};

template<bool isReadOnlyC>
struct CreationalType
{
};

template<>
struct CreationalType<true>
{
  static const boost::interprocess::open_only_t& value()
  {
    return boost::interprocess::open_only;
  }
};

template<>
struct CreationalType<false>
{
  static const boost::interprocess::open_or_create_t& value()
  {
    return boost::interprocess::open_or_create;
  }
};

template<bool isReadOnlyC>
struct AccessType
{
};

template<>
struct AccessType<true>
{
  static const boost::interprocess::mode_t value =
    boost::interprocess::read_only;
};

template<>
struct AccessType<false>
{
  static const boost::interprocess::mode_t value =
    boost::interprocess::read_write;
};

template<typename T>
class MutexedData
{
public:
  MutexedData(T* data, boost::interprocess::named_mutex& mutex)
    : m_data(data), m_mutex(mutex)
  {
    m_mutex.lock();
  }

  T& operator*() { return m_data; }
  T* operator->() { return m_data; }

  ~MutexedData() { m_mutex.unlock(); }

private:
  T* m_data;
  boost::interprocess::named_mutex& m_mutex;
};

template<bool isReadOnly, typename... Args>
class SharedMemoryManager
{
public:
  SharedMemoryManager(const std::string& name);

  template<typename T>
  typename std::enable_if<!isReadOnly, void>::type update(const T& newValue) { get() = newValue; }

  template<typename T>
  typename std::enable_if<!isReadOnly, MutexedData<T>>::type& get();

  template<typename T>
  const T& get() const;

  template<typename T>
  static constexpr int offset()
  {
    return offset<T, Args...>();
  }

  template<typename T>
  static constexpr int index()
  {
    return index<T, Args...>();
  }

  static constexpr int size() { return Size<Args...>::value; }

  ~SharedMemoryManager();

private:
  template<typename T, typename U, typename... FArgs>
  static constexpr int offset()
  {
    return Offset<std::is_same<T, U>::value, false, T, U, FArgs...>::value;
  }

  template<typename T, typename U, typename... FArgs>
  static constexpr int index()
  {
    return Index<std::is_same<T, U>::value, false, 0, T, U, FArgs...>::value;
  }

  std::string mutexName(int index);

  void initMemoryRegions();
  void initMutexes();

  template<typename T, typename... FunArgs>
  typename std::enable_if<sizeof...(FunArgs) == 1>::type init();

  template<typename T, typename... FunArgs>
  typename std::enable_if<sizeof...(FunArgs) != 1>::type init();

  const std::string m_name;
  boost::interprocess::shared_memory_object m_sharedMemory;
  std::array<boost::interprocess::mapped_region, sizeof...(Args)> m_regions;
  std::vector<boost::interprocess::named_mutex> m_mutexes;
};

template<typename... Args>
using ReadSharedMemory = SharedMemoryManager<true, Args...>;

template<typename... Args>
using SharedMemory = SharedMemoryManager<false, Args...>;

template<bool isReadOnly, typename... Args>
SharedMemoryManager<isReadOnly, Args...>::SharedMemoryManager(
  const std::string& name)
  : m_name(name), m_sharedMemory(CreationalType<isReadOnly>::value(),
                                 m_name.c_str(),
                                 AccessType<isReadOnly>::value)
{
  m_sharedMemory.truncate(this->size());
  initMemoryRegions();
}

template<bool isReadOnly, typename... Args>
void SharedMemoryManager<isReadOnly, Args...>::initMemoryRegions()
{
  init<Args...>();
}

template<bool isReadOnly, typename... Args>
std::string SharedMemoryManager<isReadOnly, Args...>::mutexName(int index)
{
  std::ostringstream oss;

  oss << m_name << index;

  return oss.str();
}

template<bool isReadOnly, typename... Args>
void SharedMemoryManager<isReadOnly, Args...>::initMutexes()
{
  constexpr int numOfArgs = sizeof...(Args);
  m_mutexes.reserve(numOfArgs);

  for(int mutexIdx = 0; mutexIdx < numOfArgs; ++mutexIdx)
  {
    auto mutex =
      boost::interprocess::named_mutex{ CreationalType<isReadOnly>::value,
                                        mutexName(mutexIdx) };

    m_mutexes.push_back(std::move(mutex));
  }
}

template<bool isReadOnly, typename... Args>
template<typename T, typename... FunArgs>
typename std::enable_if<sizeof...(FunArgs) == 1>::type
SharedMemoryManager<isReadOnly, Args...>::init()
{
  constexpr int index = this->index<T>();

  m_regions[index] = std::move(boost::interprocess::mapped_region{
    m_sharedMemory, boost::interprocess::read_write, offset<T>(), sizeof(T) });
}

template<bool isReadOnly, typename... Args>
template<typename T, typename... FunArgs>
typename std::enable_if<sizeof...(FunArgs) != 1>::type
SharedMemoryManager<isReadOnly, Args...>::init()
{
  constexpr int index = this->index<T>();

  m_regions[index] = std::move(boost::interprocess::mapped_region{
    m_sharedMemory, boost::interprocess::read_write, offset<T>(), sizeof(T) });

  init<FunArgs...>();
}

template<bool isReadOnly, typename... Args>
SharedMemoryManager<isReadOnly, Args...>::~SharedMemoryManager()
{
  boost::interprocess::shared_memory_object::remove(m_name.c_str());
}

template<bool isReadOnly, typename... Args>
template<typename T>
typename std::enable_if<!isReadOnly, MutexedData<T>>::type&
SharedMemoryManager<isReadOnly, Args...>::get()
{
  constexpr int index = this->index<T>();

  return MutexedData<T>{*reinterpret_cast<T*>(m_regions[index].get_address(), m_mutexes[index])};
}

template<bool isReadOnly, typename... Args>
template<typename T>
const T& SharedMemoryManager<isReadOnly, Args...>::get() const
{
  constexpr int index = this->index<T>();

  return MutexedData<const T>{*reinterpret_cast<T*>(m_regions[index].get_address(), m_mutexes[index])};
}
}


int main(int argc, char *argv[])
{
    lidia::SharedMemory<int, unsigned, long> sharedMemory;
    return 0;
}
