
#include "socketevent.h"
#include "config.h"
#include "datamanage.h"

#include<iostream>
using namespace std;

char serverConfigFileName[256]="../etc/server.cfg";


int main(int argc,char *argv[])
{
    DataManager::instance();
    //dzp::SocketEvent server;
    dzp::SocketEvent::instance()->ini();

    cout<<dzp::Config::instance()->getValue("LISTEN_ADDR")<<endl;
    cout<<dzp::Config::instance()->getValue("LISTEN_POTR")<<endl;


    return 0;
}