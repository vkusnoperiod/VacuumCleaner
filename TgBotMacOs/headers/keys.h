#ifndef MYTGBOTNEW_KEYS_H
#define MYTGBOTNEW_KEYS_H

#include "string"
class Keys{
public:
    Keys(){
        tg_key = "6095490209:AAGE_0tIPHzBf8x0DcAgLGZv2NErlIqmtvY";
        openai_key = "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";
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
