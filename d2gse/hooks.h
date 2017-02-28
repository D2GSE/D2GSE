#pragma once

#include <Windows.h>

struct Game;
struct Unit;

void MyHandlePacket_stub();
void D2GSGameListInsertHook_STUB();
void D2GSGameListDeleteHook_STUB();
int __stdcall MyHandlePacket(Game* game, Unit* unit, BYTE* packet, DWORD len);
void VersionInfoHook();
void WEAnnounceHook();

