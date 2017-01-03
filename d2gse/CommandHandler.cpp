#include "CommandHandler.h"
#include "Ptrs.h"
#include "Structs.h"
#include "Helpers.h"
#include <algorithm>

std::vector<CommandHandler::Handler> CommandHandler::CommandTable =
{
    { "hello", &CommandHandler::HandleHello },
    { "spawn", &CommandHandler::HandleSpawn }
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

struct ItemCodeHelper
{
    union
    {
        char szCode[4];
        DWORD code;
    };

    void Assign(std::string const& code)
    {
        if (code.length() > 3)
            return;

        memset(szCode, ' ', 4);
        memcpy(szCode, code.c_str(), code.length());
    }
};

bool CommandHandler::HandleSpawn(Game* game, Unit* player, std::vector<char const*> const& arguments)
{
    if (arguments.size() < 1)
        return false;

    ItemCodeHelper h;
    DWORD quality = ITEM_QUALITY_NORMAL;
    DWORD iLvl = 99;

    try
    {
        h.Assign(arguments[0]);
        if (arguments.size() > 1)
            quality = std::stoi(arguments[1]);
        if (arguments.size() > 2)
            iLvl = std::max(std::stoi(arguments[2]), 99);
    }
    catch (...)
    {
        return false;
    }

    SendMsgToClient(player->ptPlayerData->ptNetClient->clientID, "%sCode: %s lvl %u quality %u rawcode %u", COLOR_YELLOW, arguments[0], iLvl, quality, h.code);

    // 2 - ground, 3 - cube, 4 - inv
    //int res = SpawnItem(7, 0, 1, player, REVERSE_CC('rin '), game, 4, ITEM_QUALITY_MAGIC, 0, 0, 0);
    Unit* res = SpawnInventoryItem(iLvl, player, h.code, game, quality, 0);
    //DWORD res, itemId = D2Common_10450(REVERSE_CC('rin '), &res2);

    std::string msg = "Result: " + std::to_string((int)res);
    SendMsgToClient(player->ptPlayerData->ptNetClient->clientID, msg.c_str());
    return true;
}
