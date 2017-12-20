// g++ main.cpp --std=c++11  -lpthread

#include <iostream>
#include <thread>
#include <future>
#include <chrono>


int wait(int numOfSeconds)
{
    std::this_thread::sleep_for(std::chrono::seconds{numOfSeconds});
    return numOfSeconds;
}

int main(int argc, char *argv[])
{

    auto firstTask = std::async(wait, 2);
    auto secondTask = std::async(wait, 5);
    auto thirdTask = std::async(wait, 3);

    std::cout << firstTask.get() << " "
              << secondTask.get()<< " "
              << thirdTask.get()
              << std::endl;

    return 0;
}
