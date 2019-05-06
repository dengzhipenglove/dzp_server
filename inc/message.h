#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include<string>

class Message{
public:
    Message(char * data, int len, int fd)
    {
        data_ = std::string(data,len);
        fd_ = fd;
    }
    int getFd()
    {
        return fd_;
    }
    char* rawData()
    {
        if(string.empty())
            return NULL;
        return data_.c_str();
    }
    int DataLength()
    {
        return data_.length();
    }
private:
    std::string data_;
    std::string fd_;
};


#endif