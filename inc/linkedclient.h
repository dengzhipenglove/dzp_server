#ifndef _LINKEDCLIENTED_H_
#define _LINEEDCLIENTED_H_
#include "commondef.h"

class LinkedClient{
public:
    LinkedClient(fd ):iFd_(fd){}
    ProRead& getDataRef();
private:
    int iFd_;
    ProRead rs_;
    //unsigned int  
};


#endif