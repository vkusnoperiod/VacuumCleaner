#include<headers/methods.h>


void writeLog(const std::string& message) {
    std::ofstream logFile("../telegram_bot_log.txt", std::ios::app);
    if (logFile.is_open()) {
        // Получаем текущее время и добавляем в лог
        std::time_t currentTime = std::time(nullptr);
        logFile << std::asctime(std::localtime(&currentTime)) << ": " << message << std::endl;
        logFile.close();
    }
}

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string queryOpenAI(const std::string& message) {
    Keys keys = *new Keys();
    std::string url = "https://api.openai.com/v1/chat/completions";
    std::string response;

    CURL* curl = curl_easy_init();
    if (curl) {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + keys.getApiKey()).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        Json::Value messageObj;
        Json::Value data;
        messageObj["role"] = "user";
        messageObj["content"] = message;
        Json::Value messages;
        messages.append(messageObj);

        data["model"] = "gpt-3.5-turbo";
        data["messages"] = messages;
        Json::StreamWriterBuilder writer;
        std::string dataStr = Json::writeString(writer, data);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataStr.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<void*>(&response));

        CURLcode res = curl_easy_perform(curl);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "Error while sending request to OpenAI API: " << curl_easy_strerror(res) << std::endl;
            return "Error";
        }
    } else {
        std::cerr << "Failed to initialize cURL." << std::endl;
        return "Error";
    }

    return response;
}

std::string extractContentFromResponse(const std::string& jsonResponse) {
    Json::CharReaderBuilder builder;
    Json::Value root;
    Json::String errs;
    Json::CharReader* reader = builder.newCharReader();
    bool parsingSuccessful = reader->parse(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size(), &root, &errs);
    delete reader;

    if (!parsingSuccessful || !root["choices"].isArray() || root["choices"].empty()) {
        std::cerr << "Error while parsing JSON response from OpenAI API." << std::endl;
        return "Error";
    }

    std::string content = root["choices"][0]["message"]["content"].asString();
    return content;
}

