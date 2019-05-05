#ifndef _DATAMANAGE_H_
#define _DATAMANAGE_H_
#include <queue>

#include "message.h"

class DataManager{
public:
    DataManager();
    static DataManager* instance();
    void pushReq(Message* m);
    Message* popReq();


private:
    static DataManager* instance_;
    std::queue< Message* > requests_;
    std::queue< Message* > responses_;
    //pthread_cond_t cond_;
    //pthread_mutex_t lock_;

};


#endif