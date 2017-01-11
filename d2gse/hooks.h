#pragma once

#include <Windows.h>

struct Game;
struct Unit;

void MyHandlePacket_stub();
void InitGameInfoHook();
int __stdcall MyHandlePacket(Game* game, Unit* unit, BYTE* packet, DWORD len);
