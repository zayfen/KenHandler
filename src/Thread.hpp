#ifndef THREAD_H
#define THREAD_H

#include <memory>
#include <thread>
#include <functional>
#include <future>
#include <utility>

class Thread
{
  public:
    Thread() {
        
    }

    void Join();

    void Detach();

    template<class Function, class... Args>
    auto Run(Function&& function, Args&&... args) -> std::future<typename std::result_of<Function(Args...)>::type>;


    template<class Function, class... Args>
    auto Enqueue(Function&& function, Args&&... args) ->
            std::future<typename std::result_of<Function(Args...)>::type>
    {
        //NOTE： class result_of<F(ArgTypes...)> ; 在编译时推断出函数调用的返回类型
        using returnType = typename std::result_of<Function(Args...)>::type;
        //typedef (typename std::result_of<Function(Args...)>::type) returnType;

        //NOTE： make_shard ==> shared_ptr
        //packaged_task ==> 包装任何的可调用目标（function，lamda， bind expression etc）， 这样可以
        //异步地调用。 它的返回值和抛出的异常存在一个shared object中， 这个shared object可以通过std::future对象访问。
        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<Function>(function), std::forward<Args>(args)...));

        m_thread = std::make_shared<std::thread>(new std::thread((*task)()));
        return task->get_future();
    }
    
  private:
    std::shared_ptr<std::thread> m_thread;
    
};

#endif /* THREAD_H */
