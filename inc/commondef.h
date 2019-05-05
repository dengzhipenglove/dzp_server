#ifndef _COMMONDEF_H_
#define _COMMONDEF_H_
extern "C"
{
    #include<string.h>
}
//已经读取的套接字信息
struct ProRead{
    ProRead():curIndex(0),headLen(0),bodyLen(0),bufLen(0),buf(NULL){}
    ProRead(const ProRead& out)
    {
        curIndex = out.curIndex;
        headLen = out.headLen;
        bodyLen = out.bodyLen;
        bufLen = out.bufLen;
        buf = new char[out.bufLen];
        strcpy(buf, out.bufLen);
    }
    char* getBUf()
    {
        return buf;
    }
    void resetBuf(char* tmpbuf)
    {
        buf = tmpbuf;
    }
    ~ProRead()
    {
        if(buf)
        {
            delete[] buf;
        }
    }
    
    int curIndex;
    int headLen;
    int bodyLen;
    int bufLen;
    char* buf;
};



#endif