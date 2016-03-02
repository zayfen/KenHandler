#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H

#include "Message.hpp"

class MessageListener
{
  public:
    MessageListener() {
        
    };
    
    virtual ~MessageListener() {
        
    };

    virtual void HandleMessage(const Message& message) = 0;
};


#endif /* MESSAGELISTENER_H */
