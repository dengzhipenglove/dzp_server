#include "message.h"
#include <string>

//"Version:1.0\r\nLength:100\r\nCommand:loveAndPeace\r\nUid:0\r\nGid:0\r\n\r\n{}"
int Message::parseRawData()
{
    string::size_type pos;
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

}