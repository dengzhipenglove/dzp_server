#ifndef D_LINKEDCLIENTED_H_
#define D_LINEEDCLIENTED_H_
#include "commondef.h"

namespace dzp {

class LinkedClient
{
public:
    LinkedClient(int fd ):iFd_(fd){}
    ProRead& getDataRef();
private:
    int iFd_;
    ProRead rs_;

};
}  //namespace dzp

#endif