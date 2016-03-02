#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H

class MessageListener
{
  public:
    MessageListener();
    virtual ~MessageListener();

    virtual void HandleMessage(const Message& message) = 0;
};


#endif /* MESSAGELISTENER_H */
