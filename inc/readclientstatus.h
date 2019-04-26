#ifndef _READ_CLIENT_STATUS_H_
#define _READ_CLIENT_STATUS_H_

class ReadStatus{
public:
    ReadStatus(int fd ):fd_(fd){}
    /*
    char *getData()
    */
private:
    int fd_;
};

#endif