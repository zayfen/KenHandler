#ifndef LOOPER_H
#define LOOPER_H

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Message.hpp"
#include "MessageListener.hpp"
#include "Thread.hpp"


class Looper
{
  public:
    Looper();
    virtual ~Looper();
    void AddMessage(const Message& message);
    
    friend class Handler; // Handler can access setListener()
  private:
    void loopMessage();
    void loop();
    void setListener(std::shared_ptr<MessageListener>& l);
  private:
    std::queue<Message> m_queue; 
    std::shared_ptr<MessageListener> m_listener;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    
    std::thread* m_thread;
};


#endif /* LOOPER_H */
