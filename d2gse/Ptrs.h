#pragma once

#define NOMINMAX
#include <Windows.h>
#include <map>

#include "Structs.h"

enum DllIndexes
{
    D2GS,
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

FUNCPTR(D2Game, SpawnItem, Unit* __stdcall, (DWORD iLvl, DWORD unk1, DWORD unk2, Unit* ptPlayer, DWORD itemId, Game* ptGame, DWORD spawnTarget, DWORD quality, DWORD zero1, DWORD zero2, DWORD zero3), 0x6FC31980 - 0x6FC20000)
ASMPTR(D2Game, SpawnItem, 0x6FC31980 - 0x6FC20000)

ASMPTR(D2Game, SpawnInventoryItem, 0x2216470 - 0x21E0000)

FUNCPTR(D2Common, 10450, int __stdcall, (DWORD a1, DWORD* a2), -10450)

// .text:680018B2 66 8B 0E                          mov     cx, [esi]
// .text:680018B5 51                                push    ecx
// .text:680018B6 E8 6D 4C 00 00                    call    sub_68006528
// .text:680018BB 83 C4 04                          add     esp, 4
// .text:680018BE
// .text:680018BE                   loc_680018BE:                           ; CODE XREF: create_game_sub_68001870+3Cj
// .text:680018BE                                                           ; create_game_sub_68001870+40j
// .text:680018BE 8B C7                             mov     eax, edi
ASMPTR(D2Server, InitGameInfo, 0x6528)
ASMPTR(D2Server, InitGameInfoHook_PatchLoc, 0x18B5)
ASMPTR(D2Server, InitGameInfoHook_ReturnLoc, 0x18BE)

FUNCPTR(D2Server, GetGameInfo, DWORD *__cdecl, (WORD wGameId), 0x64E8)
FUNCPTR(D2Game, GameHashFromGameId, DWORD __stdcall, (WORD wGameId), 0x2A3B0)
FUNCPTR(D2Game, AcquireGameFromHash, Game* __stdcall, (DWORD dwHashId), 0x2AAE0)
FUNCPTR(D2Game, LeaveCriticalSection, void __fastcall, (Game* game), 0x6FC59BA0 - 0x6FC30000)

VARPTR(D2GS, MaxGames, DWORD, 0x231834)
VARPTR(D2GS, FirstGame, D2GSGame, 0x00411390 - 0x400000)
VARPTR(D2GS, GameCount, DWORD, 0x0041139C - 0x400000)
FUNCPTR(D2GS, GetPlayerFromGameByName, D2GSPlayer* __cdecl, (D2GSGame* game, const char* name), 0x00402860 - 0x400000)
FUNCPTR(D2GS, GetGameById, D2GSGame* __cdecl, (WORD wGameId), 0x402820 - 0x400000)

ASMPTR(D2Game, FindUnit, 0xE03A0)
VARPTR(D2Game, UnkStruct, DWORD, 0x6FD41C24 - 0x6FC30000)
FUNCPTR(D2Game, KickClient, void __stdcall, (DWORD dwClientId), -10003)

