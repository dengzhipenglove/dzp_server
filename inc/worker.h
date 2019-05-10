#ifndef _WORKER_H_
#define _WORKER_H_

#include<string>
#include<pthread.h>

class Worker{
    Worker(int workId, pthread_t threadId):m_workerId(workId),m_pthreadId(threadId){}
    void run();
    void doWork();
private:
    int m_workerId;
    pthread_t m_pthreadId;

};
#endif