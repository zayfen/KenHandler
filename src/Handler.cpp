#include <chrono>

#include "Handler.hpp"

Handler::Handler() {
    Handler(nullptr);
}

Handler::Handler(std::shared_ptr<Looper> looper) {
    Handler(looper, nullptr);
}

Handler::Handler(std::shared_ptr<Looper> looper, std::shared_ptr<MessageListener> l) {
    m_threadPool = std::make_shared<ThreadPool>(20);
    m_looper = std::shared_ptr<Looper>(looper);
    m_listener = std::shared_ptr<MessageListener>(l);
    m_looper->setListener(m_listener);
}

Handler::~Handler() {
    
}

void Handler::SetLooper(std::shared_ptr<Looper> looper) {

    m_looper = looper;
    this->m_looper->setListener(std::ref(m_listener));
}

void Handler::SetMessageListener(std::shared_ptr<MessageListener> l) {
    m_listener = l;
}


void Handler::PostMessage(const Message& message) {
    m_looper->AddMessage(message);
}

void Handler::PostMessageDelay(const Message& message, const int ms) {

    m_threadPool->Enqueue([&] {
            std::cout << "PostMessageDelay: " << std::endl;
            //std::chrono::milliseconds duration(ms);
            // std::chrono::microseconds usDuration(ms * 1000);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // FIXME: '20000' is ok , but 'ms' not works

            if (m_looper != nullptr) {
                m_looper->AddMessage(message);
            }
            
            std::cout << "PostMessageDelay: End" << std::endl;
        });
}
