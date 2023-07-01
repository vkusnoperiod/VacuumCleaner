#include <iostream>
#include <tgbot/tgbot.h>

int main() {
    TgBot::Bot bot("6095490209:AAGE_0tIPHzBf8x0DcAgLGZv2NErlIqmtvY");

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