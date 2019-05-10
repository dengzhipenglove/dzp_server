#include "worker.h"
#include "datamanage.h"
#include "message.h"
#include "stdio.h"

void Worker::run()
{
    while(true)
    {
        doWork();
    }
}
void Worker::doWork()
{
    Message* msg = DataManager::instance->popReq();
    if(msg == NULL)
        return ;
    if(msg->parseRawData() < 0)
        delete msg;
    printf("%s", msg->rawData());
    delete msg;
}