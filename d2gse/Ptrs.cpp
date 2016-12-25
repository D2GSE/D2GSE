#include "Ptrs.h"
#include <assert.h>

void DefineOffsets()
{
    for (auto offs = (DWORD*)OFFSETS_START; offs && offs <= (DWORD*)OFFSETS_END; ++offs)
    {
        auto dllIndex = *offs & 0xF;
        *offs >>= 8;
        if (*offs == 0xBADD)
            continue;

        char const* dllName = "";
        switch (dllIndex)
        {
            case D2Server: dllName = "d2server.dll"; break;
            case Bnclient: dllName = "Bnclient.dll"; break;
            case D2Client: dllName = "D2Client.dll"; break;
            case D2CMP: dllName = "D2CMP.dll"; break;
            case D2Common: dllName = "D2Common.dll"; break;
            case D2Game: dllName = "D2Game.dll"; break;
            case D2Net: dllName = "D2Net.dll"; break;
            case D2Win: dllName = "D2Win.dll"; break;
            case Fog: dllName = "Fog.dll"; break;
            case Storm: dllName = "Storm.dll"; break;
            default:
                assert(false && "Unknown dll index");
        }

        *offs = GetModuleOffset(dllName, *offs);
    }
}

DWORD GetModuleOffset(char const* moduleName, int Offset)
{
    auto dll = LoadLibraryA(moduleName);
    assert(dll && "Can't load library");
    if ((int)Offset < 0)
        Offset = (DWORD)GetProcAddress(dll, MAKEINTRESOURCE(-(int)Offset));
    else
        Offset += (DWORD)dll;

    return Offset;
}

