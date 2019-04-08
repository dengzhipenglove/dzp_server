
#include <stdlib.h>
#include <sys/socket.h> //socket()
#include <string.h>    //memset
#include <arpa/inet.h> //htons
#include <netinet/in.h>  //地址格式
#include <fcntl.h>
//#include <sys/epoll.h>
#include <stdio.h>

#include "socketevent.h"

#define _MAX_FDSIZE_    2048
#define _LISTEN_PORT_   11111
#define _MAX_EPOLL_EVENT_ 2048

namespace dzp {

SocketEvent::SocketEvent():listenFd(-1),epollFd(-1)
{

}
SocketEvent::~SocketEvent()
{

}

bool SocketEvent::epollInit()
{

}
bool SocketEvent::instance()
{

}

bool SocketEvent::createListener()
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

    int rc = bind( listenFd, (struct sockaddr *)&addr, sizeof(addr) );
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
void SocketEvent::setSocketOpt()
{

}

void SocketEvent::epollCreate()
{
    epollFd = epoll_create( _MAX_EPOLL_EVENT_ );
    if( epollFd < 0 )
    {
        perror("epoll create failed");
        exit(-1);
    }
}
void SocketEvent::epollAddListener( int listenfd_ )
{
    ev.events = EPOLLIN;
    ev.data.fd = listenfd_;
    if( epoll_ctl( epollFd, EPOLL_CTL_ADD, listenfd_, &ev ) == -1 )
    {
        perror( "epoll_ctl: listen_sock" );
        exit(-1);
    }
}

void SocketEvent::run()
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
        exit(-1);
    }
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
                processConnectedFD( events + i );
            }
            
        }
    }
}
void SocketEvent::processListenReq()
{
    int connFd_;
    socklen_t clilen_ = sizeof(struct sockaddr_in);
    struct sockaddr_in cliendAddr_;
    connFd_ = accept( listenFd, (struct sockaddr *)&cliendAddr_, &clilen_ );
    if( connFd_ == -1 )
        return;
    ev.events == EPOLLIN;
    ev.data.fd == connFd_;
    if( epoll_ctl( epollFd, EPOLL_CTL_ADD, connFd_, &ev) == -1 )
    {
        perror( "epoll_ctl: conn_sock" );
        exit(-1);
    }
    setNoBlock( connFd_ );
}
void SocketEvent::processConnectedFD( struct epoll_event* ev_ )
{
    
}

void SocketEvent::setNoBlock( int fd_ )
{
    int flags = fcntl( fd_, F_GETFL, 0 );
    flags = flags | O_NONBLOCK;
    fcntl( fd_, F_SETFL, flags );
}

int SocketEvent::setSocketOpt(int fd_)
{
    int rec_buffer_size = 8388608;
    int snd_buffer_size = 16777216;
    int reuseaddr = 1;
    if( setsockopt(fd_, SOL_SOCKET, SO_RCVBUF , &rec_buffer_size, sizeof(rec_buffer_size)) < 0 )
    {
        return -1;
    }
    if( setsockopt(fd_, SOL_SOCKET, SO_SNDBUF , &snd_buffer_size, sizeof(snd_buffer_size)) < 0 )
    {
        return -1;
    }
    if( setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR , &reuseaddr, sizeof(reuseaddr)) < 0 )
    {
        return -1;
    }

    return 0;
}

} //namespace dzp