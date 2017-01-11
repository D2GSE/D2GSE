#pragma once

#include "Structs.h"
#include <vector>

class CommandHandler
{
    static const int CommandCountReserve = 200;
    std::vector<D2GSCommandTable> CommandTable;

    CommandHandler();

public:
    static CommandHandler& instance()
    {
        static CommandHandler i;
        return i;
    }

    void Install();
    bool AddCommand(D2GSCommandTable const& info);

    ~CommandHandler();

};

#define sCommandHandler (CommandHandler::instance())

