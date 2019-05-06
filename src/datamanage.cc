
#include <pthread.h>
#include"datamanage.h"
#include "socketevent.h"
#include "message.h"

pthread_mutex_t lock_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_ = PTHREAD_COND_INITIALIZER;

DataManager* DataManager::instance_=NULL;
DataManager* DataManager::instance()
{
    if( instance_ == NULL )
    {
        pthread_mutex_lock(&lock_);
        if( instance_ == NULL)
            instance_ = new DataManager();
        pthread_mutex_unlock(&lock_);
    }
    return instance_;
}


DataManager::DataManager()
{

}

void DataManager::pushReq(Message*m)
{
    pthread_mutex_lock(&lock_);

    requests_.push(m);

    pthread_cond_signal(&cond_);
    pthread_mutex_unlock(&lock_);
}

Message* DataManager::popReq()
{
    Message* re =NULL;
    pthread_mutex_lock(&lock_);
    if(requests_.size() == 0)
        pthread_cond_wait(&cond_, &lock_);
    if(requests_.size() == 0)
    {
        pthread_mutex_unlock(&lock_);
        return NULL;
    }

    re = requests_.front();
    requests_.pop();
    pthread_mutex_unlock(&lock_);
    return re;
}

void DataManager::pushSnd(Message* m)
{
    pthread_mutex_lock(&lock_);

    responses_.push_back(m);

    pthread_cond_signal(&cond_);
    pthread_mutex_unlock(&lock_);   
}

void DataManager::popSndList(std::list<Message*>& l)
{
    pthread_mutex_lock(&lock_);
    //if(responses_.size() == 0)
    for(std::vector< Message* >::iterator itr = responses_.begin(); itr != responses_.end(); itr++)
    {
        l.push_back(*itr);
        SocketEvent::instance()->modFdOp((*itr)->getFd(), false);
    }
    responses_.clear();
    pthread_mutex_unlock(&lock_);
}