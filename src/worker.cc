#include "worker.h"
#include "datamanage.h"
#include "message.h"
#include "stdio.h"

void Woker::run()
{
    while(true)
    {
        doWork();
    }
}
void Woker::doWork()
{
    Message* msg = DataManager::instance->popReq();
    if(msg == NULL)
        return ;
    if(msg->parseRawData() < 0)
        delete msg;
    printf("%s", msg->rawData());
    delete msg;
}