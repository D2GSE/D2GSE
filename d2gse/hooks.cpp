#include "Hooks.h"
#include "Ptrs.h"
#include "Structs.h"
#include "CommandHandler.h"
#include "GameManager.h"
#include <string>
#include <sstream>

DWORD retAddr;
__declspec(naked) void MyHandlePacket_stub()
{
    __asm
    {
        pushad

        push [esp + 0x8 + 0x20];
        push [esp + 0x8 + 0x20];
        push edx;
        push ecx;
        call MyHandlePacket;
        test eax, eax;
        jz oldcode;

        popad;
        pop retAddr;
        pop eax;
        pop eax;
        mov eax, 1;
        push retAddr;
        ret;

    oldcode:
        popad;
        mov eax, [p_D2Server_OldPacketFunc];
        mov eax, [eax];  // 680214BE
        jmp eax;         // 68002890h
    }
}

int __stdcall MyHandlePacket(Game* game, Unit* unit, BYTE* packet, DWORD len)
{
    if (*packet == 0x15)
    {
        if (len > 7 && packet[3] == '.')
        {
            std::string message;
            message.assign((char const*)packet + 4, len - 7);
            CommandHandler::HandleMessage(game, unit, message);
            return 1;
        }

        return 0;   // block
    }

    return 0;
}

void __fastcall GameInitHook(WORD gameId)
{
    if (!gameId)
        return;

    sGameManager.GameCreated(gameId);
}

void __declspec(naked) InitGameInfoHook()
{
    __asm
    {
        pushad;
        call GameInitHook;
        popad;
        push ecx;
        call p_D2Server_InitGameInfo;
        add esp, 4;
        jmp p_D2Server_InitGameInfoHook_ReturnLoc;
    }
}
