#include <iostream>
#include <thread>
#include <future>


class A
{
public:
    A() :m_value(0) {}
    void increment()
    {
        std::unique_lock<std::mutex> (m_mutex);

        m_value++;
    }

private:
    int m_value;
    std::mutex m_mutex;
};

int main(int argc, char *argv[])
{
}
