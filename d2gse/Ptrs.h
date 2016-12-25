#pragma once

#include <Windows.h>

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

void DefineOffsets();
DWORD GetModuleOffset(char const* moduleName, int Offset);

#ifdef _DEFINE_VARS
#undef _DEFINE_VARS

#define MAKE_OFFSET(d,o) ((o << 8) | d)

#define FUNCPTR(d1,v1,t1,t2,o1)    typedef t1 d1##_##v1##_t t2; d1##_##v1##_t *p_##d1##_##v1 = (d1##_##v1##_t *)MAKE_OFFSET(d1,o1);
#define VARPTR(d1,v1,t1,o1)        t1 *p_##d1##_##v1 = (t1*)MAKE_OFFSET(d1,o1);
#define ASMPTR(d1,v1,o1)           DWORD* p_##d1##_##v1 = (DWORD*)MAKE_OFFSET(d1,o1);

#else

#define FUNCPTR(d1,v1,t1,t2,o1)    typedef t1 d1##_##v1##_t t2; extern d1##_##v1##_t *p_##d1##_##v1;
#define VARPTR(d1,v1,t1,o1)        extern t1 *p_##d1##_##v1;
#define ASMPTR(d1,v1,o1)           extern DWORD* p_##d1##_##v1;

#endif

#define OFFSETS_START &p_D2Server_PtrStart
ASMPTR(D2Server, PtrStart, 0xBADD)

// .text:68001077 FF 15 D0 D7 00 68                 call    off_6800D7D0
ASMPTR(D2Server, AfterInitialize, 0x1077)
// d2server.dll:68022348 FF 15 BE 14 02 68       call    off_680214BE
//      marsgod:68022348 FF 15 BE 14 02 68                 call    ds : dword_680214BE
ASMPTR(D2Server, OldPacketFunc_patchloc, 0x22348)
ASMPTR(D2Server, OldPacketFunc, 0x214BE)

ASMPTR(D2Server, PtrEnd, 0xBADD)
#define OFFSETS_END &p_D2Server_PtrEnd
