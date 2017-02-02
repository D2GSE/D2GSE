#pragma once

#include <Windows.h>
#include "Enums.h"

struct Game;
struct Unit;

#define REVERSE_CC(x) \
	(((x & 0xFF) << 24) | \
	((x & 0xFF00) << 8) | \
	((x & 0xFF0000) >> 8) | \
	((x & 0xFF000000) >> 24))

void SendMsgToClient(DWORD dwClientId, const char* format, ...);
void _SendMsgToClient(DWORD dwClientId, const char* format, va_list arguments);
void SendMsgToGame(Game* pGame, int dwLevel, const char* format, ...);
bool SpawnItem(DWORD iLvl, DWORD unk1, DWORD unk2, Unit* ptPlayer, DWORD itemCode, Game* ptGame, DWORD spawnTarget, DWORD quality, DWORD zero1, DWORD zero2, DWORD zero3);
Unit* SpawnInventoryItem(DWORD iLvl, Unit* ptPlayer, DWORD itemCode, Game* game, DWORD quality, DWORD dropOnNoSpace);
Unit* FindUnit(Game* game, DWORD dwUnitType, DWORD dwUnitId);
void __fastcall D2Game_LeaveCriticalSection_STUB(Game* game);

void __cdecl D2GSE_EventLog(char const* format, ...);
