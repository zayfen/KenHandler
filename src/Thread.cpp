#include "Thread.hpp"


void Thread::Join() {
    if (m_thread != nullptr && m_thread->joinable()) {
        m_thread->join();
    }
}

void Thread::Detach() {
    if (m_thread != nullptr) {
        m_thread->detach();
    }
}




    
