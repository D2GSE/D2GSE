#include "Ptrs.h"
#include <assert.h>

void DefineOffsets()
{
    for (auto itr : PtrInitInfo::InitInfos)
    {
        PtrInitInfo const* init = itr.second;
        if (!init->Offset)
            continue;

        char const* dllName = "";
        switch (init->DllIndex)
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

        *(DWORD*)itr.first = GetModuleOffset(dllName, init->Offset);
    }
}

DWORD GetModuleOffset(char const* moduleName, int Offset)
{
    auto dll = LoadLibraryA(moduleName);
    assert(dll && "Can't load library");
    if (Offset < 0)
        Offset = (DWORD)GetProcAddress(dll, MAKEINTRESOURCE(-Offset));
    else
        Offset += (DWORD)dll;

    return Offset;
}

