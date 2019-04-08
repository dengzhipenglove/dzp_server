
#include "socketevent.h"
#include "config.h"
#include<iostream>
using namespace std;

char serverConfigFileName[256]="../etc/server.cfg";


int main(int argc,char *argv[])
{
    cout<<endl<<"dafasdfasdf"<<endl;
    dzp::SocketEvent server;
    cout<<dzp::Config::instance()->getValue("LISTEN_ADDR")<<endl;
    cout<<dzp::Config::instance()->getValue("LISTEN_POTR");

    return 0;
}