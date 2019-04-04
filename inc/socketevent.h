#ifndef _SOCKET_EVENT_H_
#define _SOCKET_EVENT_H_
namespace dzp{


class socketEvent
{
    public:
        socketEvent();
        ~socketEvent();
        bool instance();
        bool epollInit();
        bool createListener();

    private:
        int epollFd;
        int listenFd;
        int listenPort;
        char listenAddr[32];
        int connFd;

};

}
#endif