#include <iostream>
#include <tgbot/tgbot.h>

int main() {
    TgBot::Bot bot("5822976994:AAHPW5pkRyOoUpqYMM-iN-HUOFj4mCvPmS4");

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Привет, я бот!");
    });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Как дела?");
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