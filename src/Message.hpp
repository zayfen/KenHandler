#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

struct Message
{
    int messageId;
    std::string messageDesc;

    Message() {
        messageId = 0;
        messageDesc = "";
    }

    Message(int id) {
        messageId = id;
        messageDesc = "";
    }
    
    Message(int id, std::string desc) {
        messageId = id;
        messageDesc = desc;
    }
};

#endif /* MESSAGE_H */
