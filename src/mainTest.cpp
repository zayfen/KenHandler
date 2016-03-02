#include "Thread.hpp"
#include "Handler.hpp"
#include "MessageListener.hpp"

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

void doSomething(std::string s, std::string to) {
    std::cout << s << to << std::endl;
}

class MyMessageListener : public MessageListener {
  public:
    void HandleMessage(const Message& message) override {
        switch (message.messageId) {
            case 1:
                std::cout << "1: " << message.messageDesc << std::endl;
                break;
                
            case 2:
                std::cout << "2: " << message.messageDesc << std::endl;
                break;

            case 3:
                std::cout << "3: " << message.messageDesc << std::endl;
                break;
        }
    }
};

int main(void)
{
    std::shared_ptr<Looper> looper(new Looper());
    std::shared_ptr<MessageListener> listener(new MyMessageListener());

    Handler h(looper, listener);

    Message m1(1, "test 1");
    h.PostMessage(m1);

    Message m2 (2, "test 2");
    h.PostMessageDelay(m2, 2);

    Message m3 (3, "test 3");
    h.PostMessage(m3);

    // h.PostRunable([&] {
    //         std::cout << "post runnale" << std::endl;
    //     });
    
    std::cout << "return" << std::endl;
    while(true) {}

    return 0;
}
