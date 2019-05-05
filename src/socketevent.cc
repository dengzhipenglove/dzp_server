
#include <stdlib.h>
#include <sys/socket.h>    //socket()
#include <string.h>        //memset
#include <arpa/inet.h>     //htons
#include <netinet/in.h>    //地址格式
#include <fcntl.h>
#include <errno.h>
//#include <string.h>
//#include <sys/epoll.h>
#include <unistd.h>        //close()
#include <stdio.h>

#include "socketevent.h"
#include "linkedclient.h"

#include "message.h"
#include "datamanage.h"
#include "commondef.h"

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
    
    setNoBlock( listenFd );

    if( setSocketOpt( listenFd )== -1 ) 
    {
        return false;
    }

    rc = listen( listenFd, 5 );
    if (rc < 0 )
    {
        printf("listen failed");
        exit(-1);
    }
    return true;
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
    //TODO
    if( nfds == -1 &&  EINTR != errno ) //&& EAGAIN != errno 
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
                process(events + i);
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
    ev.events = EPOLLIN | EPOLLERR;
    ev.data.fd = connFd_;
    setNoBlock( connFd_ );
    _client[ connFd_ ] = dzp::LinkedClient( connFd_ );
    if( epoll_ctl( epollFd, EPOLL_CTL_ADD, connFd_, &ev) == -1 )
    {
        perror( "epoll_ctl: conn_sock" );
        exit(-1);
    }
}

int SocketEvent::processConnectedFD( struct epoll_event* ev_ )
{
    return 0;
}

void SocketEvent::setNoBlock( int fd_ )
{
    int flags = fcntl( fd_, F_GETFL, 0 );
    flags = flags | O_NONBLOCK;
    fcntl( fd_, F_SETFL, flags );
}

int SocketEvent::setSocketOpt( int fd_ )
{
    int rec_buffer_size = 2097152;
    int snd_buffer_size = 4194304;
    int reuse_addr = 1;
    if( setsockopt( fd_, SOL_SOCKET, SO_RCVBUF , &rec_buffer_size, sizeof(rec_buffer_size)) < 0 )
    {
        return -1;
    }
    if( setsockopt( fd_, SOL_SOCKET, SO_SNDBUF , &snd_buffer_size, sizeof(snd_buffer_size)) < 0 )
    {
        return -1;
    }
    if( setsockopt( fd_, SOL_SOCKET, SO_REUSEADDR , &reuse_addr, sizeof(reuse_addr)) < 0 )
    {
        return -1;
    }

    return 0;
}


int SocketEvent::readFd(int fd_ )
{
    //改为引用
    ItrClient itr = _client.find(fd_);
    if(itr == _client.end())
    {
        return -1;
    }
    ProRead& rs = itr->second.getDataRef();
    //rs.
    //TODO:assign value
    int rlen = 0;
    rlen = recv( fd_, rs.buf + rs.curIndex, rs.bufLen -rs.curIndex-1, 0 );  
    if(rlen == -1)
    {
        if( errno != EINTR && errno != EAGAIN)
        {
            closeFd( fd_ );
        }
        else
        {
            /* code */
        
        }
        return -1;
        
    }
    else if(rlen == 0)
    {
        closeFd( fd_ );
    }
    else{
        rs.curIndex += rlen;
        if(rs.headLen == 0)
        {
            char* Lhead = strstr(rs.buf,"\r\n\r\n");
            char* Llen = strstr(rs.buf, "Length:");
            if( Lhead == NULL || Llen == NULL )
            {
                return 0;
            }
            rs.bodyLen = atoi(Llen);
            Lhead =Lhead + strlen("\r\n\r\n");
            rs.headLen  = Lhead - rs.buf;
            if( (rs.headLen + rs.bodyLen) > rs.bufLen )
            {
                char *newbuf = new char[rs.headLen + rs.bodyLen + 1];
                memcpy(newbuf, rs.buf, rs.curIndex);
                *(newbuf + rs.curIndex) = 0;
                delete[] rs.buf;
                rs.buf = newbuf;
                rs.bufLen = rs.headLen + rs.bodyLen + 1;
                //TODO:reset someting
            }
            if(rs.headLen + rs.bodyLen >  rs.curIndex)
            {
                return 0;//继续读取
            }
            Message* d = new Message(rs.buf,rs.headLen + rs.bodyLen ,fd_);
            //data
            DataManager::instance()->pushReq(d);




        } 

    }




}
/*
    int curIndex;
    int headLen;
    int bodyLen;
    int bufLen;
    char* buf;
*/
int SocketEvent::processReaded(ProRead& r)
{
    int remain = r.curIndex - r.headLen -r.bodyLen;
    if( remain < 0 )
        return -1;
    else if( remain == 0 )
    {
        *r.buf = 0;
        r.curIndex = r.headLen = r.bodyLen =0;
        return 0;
    }
    r.curIndex = remain;
    memcpy(r.buf, r.buf + r.headLen + r.bodyLen, remain);
    *(r.buf + remain) = 0;

    char *ibody = strstr(r.buf, "\r\n\r\n");
    char *ilen = strstr(r.buf, "Length:");
    if( ibody == NULL || ilen == NULL )
        return 0;
    ibody += strlen("\r\n\r\n");
    r.bodyLen = atoi(ilen);
    r.headLen = ibody - r.buf;
    if( r.curIndex >=(r.bodyLen + r.headLen))
        return 1;
    return 0; 
}
void SocketEvent::process(struct epoll_event* ev_ )
{

    if( (ev_->events & EPOLLERR) || (ev_->events & EPOLLHUP) )
    {
        closeFd( ev_->data.fd );
    }
    else if( (ev_->events & EPOLLIN) || (ev_->events & EPOLLPRI) )
    {
        readFd( ev_->data.fd );
    }
    else if( ev_->events & EPOLLOUT )
    {
       sendFd( ev_->data.fd );
    }    
}


void SocketEvent::readClientData(int fd_)
{
    ItrClient itr = _client.find(fd_);
    if( itr == _client.end() )
    {
        closeFd( fd_ );
    }
}

void SocketEvent::closeFd(int fd_ )
{
    epoll_ctl( epollFd, EPOLL_CTL_DEL, fd_, 0) ;
    close( fd_ );
    ItrClient itr = _client.find( fd_ );
    if( itr != _client.end() )
    {
        _client.erase( fd_ );
    }

}


} //namespace dzp