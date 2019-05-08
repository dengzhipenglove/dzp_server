#include "worker.h"
#include "datamanage.h"
#include "message.h"

void Woker::run()
{
    
}
void Woker::doWork()
{
    Message* mssg = DataManager::instance->popReq();
    if(mssg == NULL)
        return ;
    
    
}