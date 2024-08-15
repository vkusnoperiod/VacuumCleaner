#include <iostream>
#include <string>
#include <tgbot/tgbot.h>
#include<headers/keys.h>
#include<headers/methods.h>


int main() {
    Keys keys = *new Keys();
    TgBot::Bot bot(keys.getTgKey());
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Привет, я бот!");
    });
    bot.getEvents().onCommand("stop", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Новая команда");
    });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message){
        std::string user_message = message->text;
        std::string response = queryOpenAI(user_message);
        std::string finalMessage = extractContentFromResponse(response);
        writeLog(message->text);
        bot.getApi().sendMessage(message->chat->id, finalMessage);
    });

    try {
        bot.getApi().deleteWebhook();
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            bot.getApi().deleteWebhook();
            longPoll.start();
        }
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
