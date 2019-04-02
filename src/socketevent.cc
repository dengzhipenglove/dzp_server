
#include<sys/socket.h> //socket()
#include<string.h>    //memset
#include<arpa/inet.h> //htons
#include <netinet/in.h>  //地址格式
#include "socketevent.h"


#define _MAX_FDSIZE_    2048
#define _LISTEN_PORT_   11111


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
    memset((char *) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10001);
    addr.sin_addr.s_addr = inet_addr();
    listenFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}



}