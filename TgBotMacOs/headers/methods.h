#ifndef TGBOTDEV_METHODS_H
#define TGBOTDEV_METHODS_H

#include<json.h>
#include<iostream>
#include<string>
#include<fstream>
#include <ctime>
#include <tgbot/tgbot.h>
#include<headers/keys.h>


void writeLog(const std::string& message);

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output);

std::string queryOpenAI(const std::string& message);

std::string extractContentFromResponse(const std::string& jsonResponse);

#endif //TGBOTDEV_METHODS_H
