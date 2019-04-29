#ifndef _DATAMANAGE_H_
#define _DATAMANAGE_H_
#include <queue>
#include <pthread.h>
#include "message.h"

class DataManager{
public:
    DataManager()
    static DataManager* instance()
    void pushReq(Message* m);
    Message* popReq();


private:
    static DataManager* instance_;
    queue< Message* > requests_;
    queue< Message* > responses_;
    pthread_cond_t cond_;
    pthread_mutex_t lock_;

};


#endif