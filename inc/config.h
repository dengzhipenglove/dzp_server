#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <map>
#include <string>
#include <stdlib.h>


namespace dzp {
class Config{
    public:
        Config(char * configFile);
        static Config* instance();
        std::string getValue(std::string key);
        void debugPrintConfig();
    private:
        std::map<std::string,std::string> config_;
        static Config* instance_;

};


} //namespace dzp


#endif