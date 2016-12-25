#pragma once

#include <vector>
#include <Windows.h>

#define INST_JMP 0xE9
#define INST_NOP 0x90
#define INST_CALL 0xE8

class Patcher
{
public:
    static bool ReadBytes(void* pAddr, void* pData, DWORD dwLen);
    static bool WriteBytes(void* pAddr, void* pData, DWORD dwLen);

    static bool PatchJmp(void* pAddr, void* pFunc, DWORD dwLen);
    static bool PatchCall(void* pAddr, void* pFunc, DWORD dwLen);
    static bool PatchNop(void* pAddr, DWORD dwLen);

private:
    static bool PatchType(BYTE bType, void* pAddr, void* pFunc, DWORD dwLen);
};
