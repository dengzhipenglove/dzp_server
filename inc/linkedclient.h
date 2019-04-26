#ifndef _LINKEDCLIENTED_H_
#define _LINEEDCLIENTED_H_
LinkedClient{
public:
    LinkedClient():iFd_(0),data_(NULL),icurlen_(0),iheadlen_(0),ibodylen_(0){}
    ~LinkedClient(){}

private:
    int iFd_;
    char* data_;
    int  waitSendIndex_;
    int  icurlen_;
    int  iheadlen_;
    int  ibodylen_;
    //unsigned int  
}


#endif