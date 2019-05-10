
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "message.h"
using std::string;
//"Version:1.0\r\nLength:100\r\nCommand:loveAndPeace\r\nUid:0\r\nGid:0\r\n\r\n{}"
int Message::parseRawData()
{
    string::size_type pos; //数据qi'shi
    string::size_type posEnd;
    if(  std::string::npos == (pos = data_.find("Version:")))
    {
        return -1;
    }
    if( std::string::npos == (pos = data_.find("Command:")) )
    {
        return -1;
    }
    pos = pos + strlen("Command:");
    posEnd = data_.find("\r\n", pos);
    if( posEnd == std::string::npos )
    {
        return -1;
    }
    m_strCmd = data_.substr(pos, posEnd - pos);

    if( string::npos == ( pos = data_.find("Length:")) )
    {
        return -1;
    }

    pos += strlen("Length:");

    if( string::npos == ( posEnd = data_.find("\r\n", pos)) )
    {
        return -1;
    }

    m_nOuterFd = atoi( data_.substr( pos, posEnd - pos).c_str() );

    if( string::npos != ( pos = data_.find("Uid:")) &&  string::npos != (posEnd = data_.find("\r\n", pos)) )
        m_nUid = atoi( data_.substr(pos, posEnd - pos).c_str() );

    if( string::npos != ( pos = data_.find("Gid:")) && string::npos != (posEnd = data_.find("\r\n", pos)) )
        m_nGid = atoi( data_.substr(pos, posEnd - pos).c_str());
    
    if( string::npos == (pos = data_.find("\r\n\r\n")));
    {
        return -2;
    }
    //TODO: Json parse;
}