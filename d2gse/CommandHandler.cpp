#include "CommandHandler.h"
#include "Ptrs.h"
#include "Structs.h"
#include "Helpers.h"

std::vector<CommandHandler::Handler> CommandHandler::CommandTable =
{
    { "hello", &CommandHandler::HandleHello }
};

void CommandHandler::HandleMessage(Game* game, Unit* player, std::string const& message)
{
    Tokenizer args(message, ' ', 0, false);
    if (args.empty())
        return;

    for (auto& Handler : CommandTable)
    {
        if (!Handler.Callback)
            continue;

        if (!_stricmp(args[0], Handler.Command.c_str()))
        {
            args.erase(args.begin());
            Handler.Callback(game, player, args);
            return;
        }
    }
}

bool CommandHandler::HandleHello(Game* game, Unit* player, std::vector<char const*> const& arguments)
{
    std::string message = "hello world!!!1111";

    if (arguments.size() > 0)
    {
        message = "\xFF""c%s" + message;
        SendMsgToClient(player->ptPlayerData->ptNetClient->clientID, message.c_str(), arguments[0]);
    }
    else
        SendMsgToClient(player->ptPlayerData->ptNetClient->clientID, message.c_str());

    return true;
}
