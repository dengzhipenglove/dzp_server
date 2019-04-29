

#include"datamanage.h"


//pthread_mutex_t lock_ = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond_ = PTHREAD_COND_INITIALIZER;

DataManager* DataManager::instance_=NULL;
DataManager* DataManager::instance()
{
    if( instance == NULL )
    {
        pthread_mutex_lock(&lock_);
        if( instance == NULL)
            instance = new DataManager();
        pthread_mutex_unlock(&lock_);
    }
    return instance;
}


DataManager::DataManager()
{
 cond_ = PTHREAD_COND_INITIALIZER;   
 lock_ = PTHREAD_MUTEX_INITIALIZER;
}

void DataManager::pushReq(Message*m)
{
    pthread_mutex_lock(&lock_);

    requests_.push(m);

    pthread_cond_signal(&cond_);
    pthread_mutex_unlock(&locak_);
}

Message* DataNanager::popReq()
{
    Message* re =NULL;
    pthread_mutex_lock(&lock);
    if(requests_.size() == 0)
        pthread_cont_wait(&cond_,&lock);
    if(requests_.size() == 0)
    {
        pthread_mutex_unlock(&locak_);
        return NULL;
    }

    re = requests_.front();
    requests_.pop();
    pthread_mutex_unlock(&locak_);
    return re;
}