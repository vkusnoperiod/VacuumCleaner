#ifndef TGBOT_CHATSHARED_H
#define TGBOT_CHATSHARED_H

#include <cstdint>
#include <memory>

namespace TgBot {

/**
 * @brief This object contains information about the chat whose identifier was shared with the bot using a KeyboardButtonRequestChat button.
 *
 * @ingroup types
 */
class ChatShared  {

public:
    typedef std::shared_ptr<ChatShared> Ptr;

    /**
     * @brief Identifier of the request
     */
    std::int32_t requestId;

    /**
     * @brief Identifier of the shared chat.
     * 
     * The bot may not have access to the chat and could be unable to use this identifier, unless the chat is already known to the bot by some other means.
     * 
     * This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
     * But it has at most 52 significant bits, so a 64-bit integer or double-precision float type are safe for storing this identifier.
     */
    std::int64_t userId;
};
}

#endif //TGBOT_CHATSHARED_H
