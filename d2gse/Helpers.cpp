#include "Helpers.h"
#include "Ptrs.h"
#include "Structs.h"
#include <string>


Level* GetUnitLevel(Unit* unit)
{
    if (unit && unit->path && unit->path->ptRoom)
        return unit->path->ptRoom->pRoom2->pLevel;

    return NULL;
}

void SendMsgToClient(DWORD dwClientId, const char* format, ...)
{
    va_list arguments;
    va_start(arguments, format);
    _SendMsgToClient(dwClientId, format, arguments);
    va_end(arguments);
}

void _SendMsgToClient(DWORD dwClientId, const char* format, va_list arguments)
{
    BYTE text[4096];
    memset(text, 0, sizeof(text));

    char buffer[] = { 0x26,0x04,0x00,0x02,0x00,0x00,0x00,0x00,0x01,0x00,'[','S','e','r','v','e','r',']', 0x00 };
    int bufferLen = sizeof(buffer);

    memcpy(text, buffer, bufferLen);

    vsprintf((char*)&text[bufferLen], format, arguments);

    // 26 04 00 02 00 00 00 00 01 00 (Character Name) 00 (Message) 00

    int str_len = strlen((char*)&text[bufferLen]);

    D2Net_SendPacket(1, dwClientId, text, bufferLen + 1 + str_len + 1);
}

void SendMsgToGame(Game* pGame, int dwLevel, const char* format, ...)
{
    if (!pGame)
        return;

    NetClient* pClient = pGame->pClient;
    while (pClient)
    {
        bool send = true;
        if (dwLevel)
        {
            Level* lvl = GetUnitLevel(pClient->pUnit);
            if (!lvl || lvl->dwLevelNo != dwLevel)
                send = false;
        }

        if (send)
        {
            va_list args;
            va_start(args, format);
            _SendMsgToClient(pClient->clientID, format, args);
            va_end(args);
        }

        pClient = pClient->pClientPrev;
    }
}

bool SpawnItem(DWORD iLvl, DWORD unk1, DWORD unk2, Unit* ptPlayer, DWORD itemCode, Game* ptGame, DWORD spawnTarget, DWORD quality, DWORD zero1, DWORD zero2, DWORD zero3)
{
    DWORD itemId;
    DWORD ptr = D2Common_10450(itemCode, &itemId);
    if (!ptr)
        return false;

    DWORD res;
    __asm
    {
        push zero3;
        push zero2;
        push zero1;
        push quality;
        push spawnTarget;
        push ptGame;
        push itemId;
        push ptPlayer;
        mov ecx, unk2;
        mov edx, unk1;
        mov eax, iLvl;
        call p_D2Game_SpawnItem;
        mov res, eax;
    }

    return res != NULL;
}

Unit* SpawnInventoryItem(DWORD iLvl, Unit* ptPlayer, DWORD itemCode, Game* game, DWORD quality, DWORD dropOnNoSpace)
{
    Unit* res;
    __asm
    {
        push dropOnNoSpace;
        push quality;
        push game;
        mov ecx, itemCode;
        mov edx, ptPlayer;
        mov eax, iLvl;
        call p_D2Game_SpawnInventoryItem;
        mov res, eax;
    }

    return res;
}
