#pragma once

#include <Windows.h>
#include <map>

enum DllIndexes
{
    D2Server,
    Bnclient,
    D2Client,
    D2CMP,
    D2Common,
    D2Game,
    D2Net,
    D2Win,
    Fog,
    Storm
};

struct PtrInitInfo
{
    int DllIndex = 0;
    int Offset = 0;

    static std::map<void*, PtrInitInfo const*> InitInfos;

    PtrInitInfo(int DllIndex, int Offset, void* pAddrContainer) :
        DllIndex(DllIndex), Offset(Offset)
    {
        InitInfos[pAddrContainer] = this;
    }
};

void DefineOffsets();
DWORD GetModuleOffset(char const* moduleName, int Offset);

#ifdef _DEFINE_VARS
#undef _DEFINE_VARS

std::map<void*, PtrInitInfo const*> PtrInitInfo::InitInfos;

#define FUNCPTR(d1, v1, t1, t2, o1) \
    typedef t1 d1##_##v1##_t t2; \
    d1##_##v1##_t *d1##_##v1; \
    PtrInitInfo d1##_##v1##_init_info(d1, o1, &d1##_##v1);

#define VARPTR(d1, v1, t1, o1) \
    t1 *p_##d1##_##v1; \
    PtrInitInfo p_##d1##_##v1##_init_info(d1, o1, &p_##d1##_##v1);

#define ASMPTR(d1, v1, o1) \
    DWORD* p_##d1##_##v1; \
    PtrInitInfo p_##d1##_##v1##_init_info(d1, o1, &p_##d1##_##v1);

#else

#define FUNCPTR(d1, v1, t1, t2, o1) \
    typedef t1 d1##_##v1##_t t2; \
    extern d1##_##v1##_t *d1##_##v1;
#define VARPTR(d1, v1, t1, o1) \
    extern t1 *p_##d1##_##v1;
#define ASMPTR(d1, v1, o1) \
    extern DWORD* p_##d1##_##v1;

#endif

// .text:68001077 FF 15 D0 D7 00 68                 call    off_6800D7D0
ASMPTR(D2Server, AfterInitialize, 0x1077)
// d2server.dll:68022348 FF 15 BE 14 02 68       call    off_680214BE
//      marsgod:68022348 FF 15 BE 14 02 68                 call    ds : dword_680214BE
ASMPTR(D2Server, OldPacketFunc_patchloc, 0x22348)
ASMPTR(D2Server, OldPacketFunc, 0x214BE)

FUNCPTR(D2Net, SendPacket, void __stdcall, (DWORD unk1, DWORD dwClientId, BYTE* aPacket, DWORD aLen), -10002)

