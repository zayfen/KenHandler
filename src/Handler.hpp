#ifndef HANDLER_H
#define HANDLER_H

#include <memory>

#include "Looper.hpp"
#include "Message.hpp"
#include "Thread.hpp"

class Handler
{
  public:
    Handler();
    virtual ~Handler();
    void PostMessageDelay(const Message& message, unsigned long ms);
    void PostMessage(const Message& message);

    template<class Function, class... Args>
    void PostRunnable(Function&& func, Args&&... args);

    

  private:
    std::shared_ptr<Looper> m_looper;
};



#endif /* HANDLER_H */
