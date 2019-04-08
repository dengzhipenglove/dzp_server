#include <pthread.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include "config.h"

extern char serverConfigFileName[256];   //服务器基本配置文件路径名

namespace dzp{
    
Config* Config::instance_ = NULL;
pthread_mutex_t config_mutex= PTHREAD_MUTEX_INITIALIZER;
Config::Config( char * configFile )
{
    std::ifstream inFile( configFile, std::ios::in);
    if(inFile.is_open())
    {
        std::string line;
        std::string::size_type index;
        while( getline(inFile, line) )
        {
            index = line.find('=');
            if( line.empty() || line[0] == '#' || index == std::string::npos )
                continue;
            config_[line.substr(0, index)] = line.substr( index + 1 );
        }

        inFile.close();
        return;
    }
    printf("failed to open %s",configFile);
    exit(-1);
}


Config* Config::instance()
{
    if( instance_  == NULL )
    {
        pthread_mutex_lock( &config_mutex );
        if( instance_ == NULL)
        {
            instance_ = new Config( serverConfigFileName );
        }
        pthread_mutex_unlock( &config_mutex );
    }
    return instance_;
}

std::string Config::getValue(std::string key)
{
    std::map<std::string,std::string>::iterator itr = config_.find(key);
    if( itr == config_.end())
        return "";
    return itr->second;
}

void Config::debugPrintConfig()
{
    if( config_.size() == 0 )
    {
        return;
    }
    for( std::map<std::string,std::string>::iterator itr = config_.begin(); itr != config_.end(); ++itr )
    {
        printf("-%s = %s-\n",itr->first.c_str(),itr->second.c_str());
    }
}


}//namespace dzp