#include "Hooks.h"
#include "Ptrs.h"
#include <string>
#include <sstream>

DWORD retAddr;
__declspec(naked) void MyHandlePacket_stub()
{
    __asm
    {
        pushad

        push [esp + 0x8 + 0x20];
        push [esp + 0x8 + 0x20];
        push edx;
        push ecx;
        call MyHandlePacket;
        test eax, eax;
        jz oldcode;

        popad;
        pop retAddr;
        pop eax;
        pop eax;
        mov eax, 1;
        push retAddr;
        ret;

    oldcode:
        popad;
        mov eax, [p_D2Server_OldPacketFunc];
        mov eax, [eax];  // 680214BE
        jmp eax;         // 68002890h
    }
}

int __stdcall MyHandlePacket(DWORD a1, DWORD a2, BYTE* packet, DWORD len)
{
    if (*packet == 0x15)
        return 1;   // block

    return 0;
}
