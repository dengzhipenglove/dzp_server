#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include<string>

class Message{
public:
    Message(char * data, int len, int fd):
    {
        data_ = std::string(data,len);
        fd_ = fd;
    }
private:
    string data_;
    string fd_;
};


#endif