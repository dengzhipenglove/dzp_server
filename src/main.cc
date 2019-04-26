
#include "socketevent.h"
#include "config.h"
#include<iostream>
using namespace std;

char serverConfigFileName[256]="../etc/server.cfg";


int main(int argc,char *argv[])
{
    dzp::SocketEvent server;
    cout<<dzp::Config::instance()->getValue("LISTEN_ADDR")<<endl;
    cout<<dzp::Config::instance()->getValue("LISTEN_POTR")<<endl;

    return 0;
}