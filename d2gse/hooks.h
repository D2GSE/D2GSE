#pragma once

#include <Windows.h>

struct Game;
struct Unit;

void MyHandlePacket_stub();
int __stdcall MyHandlePacket(Game* game, Unit* unit, BYTE* packet, DWORD len);
