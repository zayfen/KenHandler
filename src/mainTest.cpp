#include "Thread.hpp"

#include <string>
#include <chrono>
#include <thread>
#include <iostream>

int print(std::string s, int count, int interval) {

    for (int i = 0; i < count; i++) {
        std::cout << s << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
    return 10;
}

int main(void)
{
    Thread t;
    t.Enqueue(std::move(print), std::move(std::string("hello")), std::move(int(5)), std::move(int(1)));  // ok

    //t.Run(print, std::string("hello"), 5, 5);

    t.Join();
    return 0;
}
