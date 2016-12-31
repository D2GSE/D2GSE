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
