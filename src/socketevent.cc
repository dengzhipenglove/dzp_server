
#include<sys/socket.h> //socket()
#include<string.h>    //memset
#include<arpa/inet.h> //htons
#include <netinet/in.h>  //地址格式
#include <sys/epoll.h>
#include<stdio.h>
#include "socketevent.h"

#define _MAX_FDSIZE_    2048
#define _LISTEN_PORT_   11111
#define _MAX_EPOLL_EVENT_ 2048

namespace dzp{
socketEvent::socketEvent():listenFd(-1),epollFd(-1)
{

}
socketEvent::~socketEvent()
{

}

bool socketEvent::epollInit()
{

}
bool socketEvent::instance()
{

}

bool socketEvent::createListener()
{
    struct sockaddr_in addr;
    memset( (char *) &addr, 0, sizeof(addr) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( listenPort );
    addr.sin_addr.s_addr = inet_addr( listenAddr );

    listenFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if( listenFd < 0 )
    {
        printf("create socket failed");
        exit(-1);
    }

    int rc = bind( listenFd, (struct sockaddr *)&addr, sizeof(addr) )
    if( rc < 0 )
    {
        printf("bind socket failed");
        exit(-1);
    }

    rc = listen( listenFd, 5 );
    if (rc < 0 )
    {
        printf("listen failed");
        exit(-1);
    }
    return true;
}
void socketEvent::setSocketOpt()
{

}

void socketEvent::epollCreate()
{
    epollFd = epoll_create( _MAX_EPOLL_EVENT_ );
    if( epollFd < 0 )
    {
        perror("epoll create failed");
        exit(-1);
    }
}
void socketEvent::epollAddListener( int listenfd_ )
{
    ev.enents = EPOLLIN;
    ev.data.fd = listenfd_;
    if( epoll_ctl( epollFd, EPOLL_CTL_ADD, listenfd_, &ev ) == -1 )
    {
        perror( "epoll_ctl: listen_sock" );
        exit(-1);
    }
}

void socketEvent::run()
{
    if( epollFd == -1 )
    {
        printf("run failed:epollFd=-1");
    }
    int nfds = -1;
    nfds = epoll_wait( epollFd, events, _MAX_EPOLL_EVENT_, -1 );

    if( nfds == -1 )
    {
        perror("epoll wait nfds = -1");
        return -1;
    }
    /*else if( nfds == 0 )
    {
        //TODO::timeout
    }
    */
    else
    {
        for( int i = 0; i < nfds ; ++i )
        {
            if( events[i].data.fd == listenFd )
            {       
                processListenReq();
            }
            else
            {
                processConnectedFD(events[i].data.fd);
            }
            
        }
    }
}
void socketEvent::processListenReq()
{
    int connFd_;
    socklen_t clilen_;
    struct sockaddr_in cliendAddr_;
    connFd_ = accept( listenFd, (struct sockaddr *)cliendAddr_, &clilen_ );
    if( connFd_ == -1 )
        return;
    ev.events == EPOLLIN;
    ev.fd.data == connFd_;
    if( epoll_ctl( epollFd, EPOLL_CTL_ADD, connFd_, &ev) == -1 )
    {
        perror( "epoll_ctl: conn_sock" );
        exit(-1);
    }
}
void socketEvent::processConnectedFD( int fd_)
{
    
}