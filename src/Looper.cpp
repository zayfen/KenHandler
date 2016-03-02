#include <iostream>

#include "Looper.hpp"

Looper::Looper() {
    m_listener = nullptr;
    m_thread = nullptr;

    loopMessage();
}

Looper::~Looper() {
    if (m_thread != nullptr) {
        AddMessage(Message(-1));
        m_thread->join();
        delete m_thread;
    }
}

void Looper::AddMessage(const Message& message) {
     // Add message
    {
        std::lock_guard<std::mutex> lk(this->m_mutex);
        this->m_queue.push(message);
    }
    this->m_condition.notify_one();
    std::cout << "Add a message finished" << std::endl;
}

void Looper::loopMessage() {

    m_thread = new std::thread([&] {
            loop();
        });
}

void Looper::loop() {
    while (true) {
        std::cout << "loop()" << std::endl;
        std::unique_lock<std::mutex> lk(this->m_mutex);
        this->m_condition.wait(lk, [&] { return !m_queue.empty();});

        Message msg = m_queue.front();
        m_queue.pop();
        std::cout << "loop() receive a notify: " << msg.messageId << " " << msg.messageDesc << std::endl;
        if (msg.messageId == -1) {
            break;
        }
        if (m_listener != nullptr) {
            m_listener->HandleMessage(msg);
        } else {
            std::cout << " listener is nullptr" << std::endl;
        }
    }
}

void Looper::setListener(std::shared_ptr<MessageListener>& l) {
    m_listener = l;
}
