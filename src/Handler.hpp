#ifndef HANDLER_H
#define HANDLER_H

#include <memory>

#include "Looper.hpp"
#include "Message.hpp"
#include "Thread.hpp"
#include "MessageListener.hpp"
#include "ThreadPool.hpp"

class Handler
{
  public:
    Handler();
    
    Handler(std::shared_ptr<Looper> looper);
    
    Handler(std::shared_ptr<Looper> looper, std::shared_ptr<MessageListener> l);
    
    virtual ~Handler();
    
    void SetLooper(std::shared_ptr<Looper> looper);
    
    void SetMessageListener(std::shared_ptr<MessageListener> l);
    
    void PostMessageDelay(const Message& message, const int ms);
    
    void PostMessage(const Message& message);
    
    // template<class Function, class... Args>
    // auto PostRunable(Function&& function, Args&&... args) ->
    //         std::future<typename std::result_of<Function(Args...)>::type>
    // {
    //     using returnType = typename std::result_of<Function(Args...)>::type;
    //     auto task = std::make_shared<std::packaged_task<returnType()>>(
    //         std::bind(std::forward<Function>(function), std::forward<Args>(args)...));
    //     m_threadPool->Enqueue([&] {
    //             (*task)();
    //         });
    //     return task->get_future();
    // }



  private:
    std::shared_ptr<Looper> m_looper;
    std::shared_ptr<MessageListener> m_listener;
    std::shared_ptr<ThreadPool> m_threadPool;
};



#endif /* HANDLER_H */
