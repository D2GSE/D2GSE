#include "CommandHandler.h"
#include "Ptrs.h"
#include "Patcher.h"
#include <string>

#pragma comment(lib, "wsock32.lib")

CommandHandler::CommandHandler()
{
    CommandTable.reserve(CommandCountReserve);
}


CommandHandler::~CommandHandler()
{
}

int __cdecl TestCommandHandle(SOCKET s, void*)
{
    std::string message = "Dont even try to do this...\r\n";
    return send(s, message.c_str(), message.length(), 0);
}

void CommandHandler::Install()
{
    CommandTable.clear();
    D2GSCommandTable* tableStart = p_D2GS_CommandTable;

    while (tableStart->Command)
    {
        CommandTable.push_back(*tableStart);
        ++tableStart;
    }

    CommandTable.push_back(D2GSCommandTable());

    D2GSCommandTable* newTableStart = CommandTable.data();

    Patcher::WriteBytes((void*)((DWORD)p_D2GS_CommandTable_PatchLoc1 + 2), &newTableStart, 4);
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_CommandTable_PatchLoc2 + 1), &newTableStart, 4);
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_CommandTable_PatchLoc3 + 3), &newTableStart, 4);
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_CommandTable_PatchLoc4 + 1), &newTableStart, 4);
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_CommandTable_PatchLoc5 + 1), &newTableStart, 4);

    void* newHiddenStart = &newTableStart->Hidden;
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_CommandTable_PatchLocHidden + 4), &newHiddenStart, 4);
    void* newHandlerStart = &newTableStart->Handler;
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_CommandTable_PatchLocHandler + 3), &newHandlerStart, 4);
    void* newParamDescrStart = &newTableStart->ParameterDescription;
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_CommandTable_PatchLocParameter + 1), &newParamDescrStart, 4);
    void* newDescrStart = &newTableStart->Description;
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_CommandTable_PatchLocDescription + 1), &newDescrStart, 4);

    D2GSCommandTable newCommand;
    newCommand.Command = "fuckadmin";
    newCommand.Hidden = 0;
    newCommand.Description = "Fuck this GS admin";
    newCommand.Handler = &TestCommandHandle;
    AddCommand(newCommand);
}

bool CommandHandler::AddCommand(D2GSCommandTable const& info)
{
    if (CommandTable.size() == CommandTable.capacity())
        return false;

    CommandTable[CommandTable.size() - 1] = info;
    CommandTable.push_back(D2GSCommandTable());
    return true;
}
