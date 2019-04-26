#ifndef _CLIENT_H_
#define _CLIENT_H_

class Client{
public:
    Clinet(int fd):fd_(fd){}
private:
    int fd_;
};


#endif