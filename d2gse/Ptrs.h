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
ASMPTR(D2Game, FindUnit, 0xE03A0)
VARPTR(D2Game, UnkStruct, DWORD, 0x6FD41C24 - 0x6FC30000)
FUNCPTR(D2Game, KickClient, void __stdcall, (DWORD dwClientId), -10003)

VARPTR(D2GS, MaxGames, DWORD, 0x231834)
VARPTR(D2GS, FirstGame, D2GSGame, 0x00411390 - 0x400000)
VARPTR(D2GS, GameCount, DWORD, 0x0041139C - 0x400000)
FUNCPTR(D2GS, GetPlayerFromGameByName, D2GSPlayer* __cdecl, (D2GSGame* game, const char* name), 0x00402860 - 0x400000)
FUNCPTR(D2GS, GetGameById, D2GSGame* __cdecl, (WORD wGameId), 0x402820 - 0x400000)

VARPTR(D2GS, CharlistSize, DWORD, 0x00411384 - 0x400000)
FUNCPTR(D2GS, HashPlayerName, int __cdecl, (const char* name), 0x004015F0 - 0x400000)
VARPTR(D2GS, CharlistTable, D2GSCharacterInfo**, 0x00411388 - 0x400000)
FUNCPTR(D2GS, GetDatabasePlayerInfo, DatabasePlayerInfo* __cdecl, (char *Name, int param), 0x00401770 - 0x400000) // 1 - player info, 2 - game info

VARPTR(D2GS, CommandTable, D2GSCommandTable, 0x0040F780 - 0x400000)
// .text:00408A57 8B 35 80 F7 40 00                 mov     esi, commandStart
ASMPTR(D2GS, CommandTable_PatchLoc1, 0x00408A57 - 0x400000)
// .text:00408A6B BF 80 F7 40 00                    mov     edi, offset commandStart
ASMPTR(D2GS, CommandTable_PatchLoc2, 0x00408A6B - 0x400000)
// .text:00408BFA 8B 04 8D 80 F7 40 00              mov     eax, commandStart[ecx * 4]
ASMPTR(D2GS, CommandTable_PatchLoc3, 0x00408BFA - 0x400000)
// .text:004092F3 A1 80 F7 40 00                    mov     eax, commandStart
ASMPTR(D2GS, CommandTable_PatchLoc4, 0x004092F3 - 0x400000)
// .text:004092FD BE 80 F7 40 00                    mov     esi, offset commandStart
ASMPTR(D2GS, CommandTable_PatchLoc5, 0x004092FD - 0x400000)

// .text:0040930C C7 44 24 10 84 F7 40 00           mov[esp + 114h + var_104], offset hiddenStart
ASMPTR(D2GS, CommandTable_PatchLocHidden, 0x0040930C - 0x400000)
// .text:00408AC3 8B 04 85 88 F7 40 00              mov     eax, handlerStart[eax * 4]
ASMPTR(D2GS, CommandTable_PatchLocHandler, 0x00408AC3 - 0x400000)
// .text:00409302 BD 8C F7 40 00                    mov     ebp, offset parameterDescr
ASMPTR(D2GS, CommandTable_PatchLocParameter, 0x00409302 - 0x400000)
// .text:00409307 BB 90 F7 40 00                    mov     ebx, offset descriptionStart
ASMPTR(D2GS, CommandTable_PatchLocDescription, 0x00409307 - 0x400000)

