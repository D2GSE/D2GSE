#include "Hooks.h"
#include "Ptrs.h"
#include "Structs.h"
#include "ChatHandler.h"
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
            ChatHandler::HandleCommand(game, unit, message);
            return 1;
        }

        return 0;   // block
    }

    return 0;
}

void __fastcall D2GSGameListInsertHook(D2GAMEINFO* gameInfo)
{
    if (!gameInfo)
        return;

    sGameManager.GameCreated(gameInfo);
}

void __fastcall D2GSGameListDeleteHook(D2GAMEINFO* gameInfo)
{
    if (!gameInfo)
        return;

    sGameManager.GameClosed(gameInfo);
}

void __declspec(naked) D2GSGameListInsertHook_STUB()
{
    __asm
    {
        mov dword ptr[esi + 0x80], 0;
        pushad;
        mov ecx, esi;
        call D2GSGameListInsertHook;
        popad;
        mov eax, p_D2GS_D2GSGameListInsert_Patchloc;
        add eax, 0xA;
        jmp eax;
    }
}

void __declspec(naked) D2GSGameListDeleteHook_STUB()
{
    __asm
    {
        pushad;
        mov ecx, [esp + 0x20 + 4];
        call D2GSGameListDeleteHook;
        popad;
        push esi;
        mov esi, [esp + 4 + 4];
        mov eax, p_D2GS_D2GSGameListDelete_Patchloc;
        add eax, 5;
        jmp eax;
    }
}

char const* D2GSEInfo = "D2GSE Version 0.1 build on " __DATE__ " " __TIME__;

void __declspec(naked) VersionInfoHook()
{
    __asm
    {
        call D2Server_sub_68003430;
        push D2GSEInfo;
        push 0;
        push 4;
        push 4;
        push esi;
        call D2Server_sub_68003430;
        mov eax, p_D2Server_VersionInfo_Patchloc;
        add eax, 5;
        jmp eax;
    }
}
