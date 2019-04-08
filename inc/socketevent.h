#ifndef _SOCKET_EVENT_H_
#define _SOCKET_EVENT_H_
#include <sys/epoll.h>

namespace dzp {

class SocketEvent
{
    public:
        SocketEvent();
        ~SocketEvent();
        bool instance();
        bool epollInit();
        bool createListener();
        void setSocketOpt();
        void epollCreate();
        void epollAddListener( int listenfd_ );
        void run();
        void processConnectedFD(struct epoll_event* ev_ );
        void processListenReq();
        void setNoBlock( int fd_ );
        int setSocketOpt(int fd_);

    private:
        
        int listenFd; 
        int listenPort;
        char listenAddr[32];
        //int connFd;

        int epollFd;
        struct epoll_event ev;
        struct epoll_event events[2048];

};

}
#endif