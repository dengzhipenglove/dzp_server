#ifndef _SOCKET_EVENT_H_
#define _SOCKET_EVENT_H_
#include <sys/epoll.h>

#include <map>
#include <string>


#include "linkedclient.h"
#include "commondef.h"

using std::string;

namespace dzp {

class SocketEvent
{
    public:
        SocketEvent();
        ~SocketEvent();
        static SocketEvent* instance();
        bool epollInit();
        void ini();
        bool createListener();
        void epollCreate();
        void epollAddListener( int listenfd_ );
        void run();
        int processConnectedFD(struct epoll_event* ev_ );
        void processListenReq();
        void setNoBlock( int fd_ );
        int setSocketOpt( int fd_ );
        int readFd(int fd_ );
        int sendFd(int fd_ );
        void process(struct epoll_event* ev_ );
        void readClientData(int fd_);
        void closeFd(int fd_ );
        int processReaded(ProRead& r);
        int modFdOp(int fd ,bool b=true);
        int realSendData(int fd,const char * data, int size);

    private:  
        static SocketEvent* instance_;
        typedef std::map<int,dzp::LinkedClient>::iterator ItrClient;
        typedef std::map<int, dzp::LinkedClient> ClientType;
        
        int listenFd; 
        int listenPort;
        char listenAddr[32];
        //int connFd;

        int epollFd;
        struct epoll_event ev;
        struct epoll_event events[2048];

        ClientType _client;


};

}
#endif