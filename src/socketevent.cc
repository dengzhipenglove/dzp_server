
#include<sys/socket.h>
#include<string.h>
//#include <netinet/in.h>
#include "socketevent.h"


#define _MAX_FDSIZE_    2048

namespace dzp{
socketEvent::socketEvent()
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
    listenFd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
}



}