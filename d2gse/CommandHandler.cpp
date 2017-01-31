#include "CommandHandler.h"
#include "Ptrs.h"
#include "Patcher.h"
#include "hooks.h"
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
    ADMINCOMMAND* tableStart = p_D2GS_admincmdtbl;

    while (tableStart->keyword)
    {
        CommandTable.push_back(*tableStart);
        ++tableStart;
    }

    CommandTable.push_back(ADMINCOMMAND());

    ADMINCOMMAND* newTableStart = CommandTable.data();

    Patcher::WriteBytes((void*)((DWORD)p_D2GS_admincmdtbl_patchloc1 + 2), &newTableStart, 4);
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_admincmdtbl_patchloc2 + 1), &newTableStart, 4);
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_admincmdtbl_patchloc3 + 3), &newTableStart, 4);
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_admincmdtbl_patchloc4 + 1), &newTableStart, 4);
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_admincmdtbl_patchloc5 + 1), &newTableStart, 4);

    void* newHiddenStart = &newTableStart->Hidden;
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_admincmdtbl_patchlocHidden + 4), &newHiddenStart, 4);
    void* newHandlerStart = &newTableStart->adminfunc;
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_admincmdtbl_patchlocHandler + 3), &newHandlerStart, 4);
    void* newParamDescrStart = &newTableStart->param;
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_admincmdtbl_patchlocParameter + 1), &newParamDescrStart, 4);
    void* newDescrStart = &newTableStart->annotation;
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_admincmdtbl_patchlocDescription + 1), &newDescrStart, 4);

    ADMINCOMMAND newCommand;
    newCommand.keyword = "fuckadmin";
    newCommand.Hidden = 0;
    newCommand.annotation = "Fuck this GS admin";
    newCommand.adminfunc = &TestCommandHandle;
    AddCommand(newCommand);

    Patcher::PatchJmp(p_D2Server_VersionInfo_Patchloc, VersionInfoHook, 5);

    CopyrightInfo.reserve(CopyrightCountReserve);
    char** copyright = p_D2Server_CopyrightStruct;
    while (*copyright)
    {
        CopyrightInfo.push_back(*copyright);
        ++copyright;
    }

    CopyrightInfo.push_back(" ");
    CopyrightInfo.push_back("D2GSE Extension Library (C) 2017 by Dramacydal (http://github.com/D2GSE)");
    CopyrightInfo.push_back((char*)nullptr);

    void* newCopyright = CopyrightInfo.data();
    Patcher::WriteBytes((void*)((DWORD)p_D2Server_Copyright_Patchloc_1 + 1), &newCopyright, 4);
    Patcher::WriteBytes((void*)((DWORD)p_D2Server_Copyright_Patchloc_2 + 1), &newCopyright, 4);
}

bool CommandHandler::AddCommand(ADMINCOMMAND const& info)
{
    if (CommandTable.size() == CommandTable.capacity())
        return false;

    CommandTable[CommandTable.size() - 1] = info;
    CommandTable.push_back(ADMINCOMMAND());
    return true;
}
