#ifndef _WORKER_H_
#define _WORKER_H_

#include<string>
#include<pthread>

class Worker{
    Worker(int workId, pthread_t threadId):worker_id_(workId),pthread_id_(threadId){}
    void run()
private:
    int worker_id_;
    pthread_t pthread_id_;

};
#endif