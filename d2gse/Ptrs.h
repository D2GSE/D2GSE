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

VARPTR(D2Server, CopyrightStruct, char*, 0x6800F124 - 0x68000000)
ASMPTR(D2Server, Copyright_Patchloc_1, 0x6800370D - 0x68000000)
ASMPTR(D2Server, Copyright_Patchloc_2, 0x68003717 - 0x68000000)
FUNCPTR(D2Server, sub_68003430, int __stdcall, (int a1, char a2, char a3, void *a4, void *a5), 0x68003430 - 0x68000000)
// .text:68003679 E8 B2 FD FF FF                    call    sub_68003430
ASMPTR(D2Server, VersionInfo_Patchloc, 0x68003679 - 0x68000000)

FUNCPTR(D2Game, GameHashFromGameId, DWORD __stdcall, (WORD wGameId), 0x2A3B0)
FUNCPTR(D2Game, AcquireGameFromHash, Game* __stdcall, (DWORD dwHashId), 0x2AAE0)
ASMPTR(D2Game, LeaveCriticalSection, 0x6FC59BA0 - 0x6FC30000)
ASMPTR(D2Game, FindUnit, 0xE03A0)
VARPTR(D2Game, UnkStruct, DWORD, 0x6FD41C24 - 0x6FC30000)
FUNCPTR(D2Game, KickClient, void __stdcall, (DWORD dwClientId), -10003)

VARPTR(D2GS, csGameList, CRITICAL_SECTION, 0x006317C0 - 0x400000)
VARPTR(D2GS, MaxGames, DWORD, 0x231834)
VARPTR(D2GS, lpGameInfoHead, D2GAMEINFO, 0x00411390 - 0x400000)
VARPTR(D2GS, currentgamenum, DWORD, 0x0041139C - 0x400000)
FUNCPTR(D2GS, D2GSFindCharInGameByCharName, D2CHARINFO* __cdecl, (D2GAMEINFO* game, const char* name), 0x00402860 - 0x400000)
FUNCPTR(D2GS, D2GSFindGameInfoByGameId, D2GAMEINFO* __cdecl, (WORD wGameId), 0x402820 - 0x400000)
VARPTR(D2GS, lpPendingChar, D2CHARINFO, 0x00411394 - 0x400000)
FUNCPTR(D2GS, D2GSFindPendingCharByCharName, D2CHARINFO* __cdecl, (const char* name), 0x004028E0 - 0x400000)

VARPTR(D2GS, clitbl_len, DWORD, 0x00411384 - 0x400000)
FUNCPTR(D2GS, string_hash, int __cdecl, (const char* name), 0x004015F0 - 0x400000)
VARPTR(D2GS, clitbl, D2CHARLIST*, 0x00411388 - 0x400000)
FUNCPTR(D2GS, charlist_getdata, CharlistInfo* __cdecl, (char *Name, int param), 0x00401770 - 0x400000) // 1 - player info, 2 - game info

// .text:004022F5 C7 86 80 00 00 00 00 00 00 00                 mov     dword ptr[esi + 80h], 0
ASMPTR(D2GS, D2GSGameListInsert_Patchloc, 0x004022F5 - 0x400000);
// .text:00402360 56                                            push    esi
ASMPTR(D2GS, D2GSGameListDelete_Patchloc, 0x00402360 - 0x400000);

VARPTR(D2GS, admincmdtbl, ADMINCOMMAND, 0x0040F780 - 0x400000)
// .text:00408A57 8B 35 80 F7 40 00                 mov     esi, commandStart
ASMPTR(D2GS, admincmdtbl_patchloc1, 0x00408A57 - 0x400000)
// .text:00408A6B BF 80 F7 40 00                    mov     edi, offset commandStart
ASMPTR(D2GS, admincmdtbl_patchloc2, 0x00408A6B - 0x400000)
// .text:00408BFA 8B 04 8D 80 F7 40 00              mov     eax, commandStart[ecx * 4]
ASMPTR(D2GS, admincmdtbl_patchloc3, 0x00408BFA - 0x400000)
// .text:004092F3 A1 80 F7 40 00                    mov     eax, commandStart
ASMPTR(D2GS, admincmdtbl_patchloc4, 0x004092F3 - 0x400000)
// .text:004092FD BE 80 F7 40 00                    mov     esi, offset commandStart
ASMPTR(D2GS, admincmdtbl_patchloc5, 0x004092FD - 0x400000)

// .text:0040930C C7 44 24 10 84 F7 40 00           mov[esp + 114h + var_104], offset hiddenStart
ASMPTR(D2GS, admincmdtbl_patchlocHidden, 0x0040930C - 0x400000)
// .text:00408AC3 8B 04 85 88 F7 40 00              mov     eax, handlerStart[eax * 4]
ASMPTR(D2GS, admincmdtbl_patchlocHandler, 0x00408AC3 - 0x400000)
// .text:00409302 BD 8C F7 40 00                    mov     ebp, offset parameterDescr
ASMPTR(D2GS, admincmdtbl_patchlocParameter, 0x00409302 - 0x400000)
// .text:00409307 BB 90 F7 40 00                    mov     ebx, offset descriptionStart
ASMPTR(D2GS, admincmdtbl_patchlocDescription, 0x00409307 - 0x400000)

FUNCPTR(D2GS, D2GSEventLog, int __cdecl, (char const*, char const* Format, ...), 0x00403F40 - 0x400000)

VARPTR(D2GS, D2GSConfig, D2GSConfigEntry, 0x40D030 - 0x400000)
FUNCPTR(D2GS, D2GSReadConfig, int __stdcall, (),  0x004019C0 - 0x400000)
// .text:004019C0 68 30 D0 40 00                                push    offset off_40D030 ; int
ASMPTR(D2GS, Config_PatchLoc, 0x004019C0 - 0x400000)

FUNCPTR(D2GS, chat_message_announce_char2, int __cdecl, (int a1, int a2, int a3), 0x00403450 - 0x400000)
ASMPTR(D2GS, CustomWEAnnounce_PatchLoc, 0x004035D9 - 0x400000)

typedef D2GSWEConfigInfo const* (*GetWeInfoFunc)();
VARPTR(D2GS, GetWEConfig, GetWeInfoFunc, 0x004113E0 - 0x400000)

