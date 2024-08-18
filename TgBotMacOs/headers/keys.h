#ifndef MYTGBOTNEW_KEYS_H
#define MYTGBOTNEW_KEYS_H

#include "string"
class Keys{
public:
    Keys(){
        tg_key = "";
        openai_key = "";
    }

    std::string getApiKey(){
        return openai_key;
    }
    std::string getTgKey(){
        return tg_key;
    }
private:
    std::string openai_key;
    std::string tg_key;
};
#endif //MYTGBOTNEW_KEYS_H
