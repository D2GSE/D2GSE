#pragma once

#include <Windows.h>

void MyHandlePacket_stub();
int __stdcall MyHandlePacket(DWORD a1, DWORD a2, BYTE* packet, DWORD len);
