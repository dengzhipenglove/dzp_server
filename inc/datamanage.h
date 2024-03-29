#ifndef _DATAMANAGE_H_
#define _DATAMANAGE_H_
#include <queue>
#include <list>
#include <vector>
#include "message.h"

class DataManager{

public: 
    DataManager();
    static DataManager* instance();
// recvived
    void pushReq(Message* m);
    Message* popReq();

// waitting to send
    void pushSnd(Message* m);
    void popSndList(std::list<Message*>& l);



private:
    static DataManager* instance_;
    std::queue< Message* > requests_;
    std::vector< Message* > responses_;
    //pthread_cond_t cond_;
    //pthread_mutex_t lock_;

};


#endif