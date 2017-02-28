#pragma once

#include "Structs.h"
#include <vector>

class CommandHandler
{
    static const int CommandCountReserve = 200;
    std::vector<ADMINCOMMAND> CommandTable;

    static const int CopyrightCountReserve = 20;
    std::vector<char*> CopyrightInfo;

    CommandHandler();
    void FillCustomCommands();

public:
    static CommandHandler& instance()
    {
        static CommandHandler i;
        return i;
    }

    void Install();
    bool AddCommand(ADMINCOMMAND const& info);

    ~CommandHandler();

};

#define sCommandHandler (CommandHandler::instance())

