#include "Patcher.h"

bool Patcher::WriteBytes(void* pAddr, void* pData, DWORD dwLen)
{
    DWORD dwOld;

    if (!VirtualProtect(pAddr, dwLen, PAGE_READWRITE, &dwOld))
        return false;

    memcpy(pAddr, pData, dwLen);
    return VirtualProtect(pAddr, dwLen, dwOld, &dwOld) != 0;
}

bool Patcher::ReadBytes(void* pAddr, void* pData, DWORD dwLen)
{
    DWORD dwOld;
    if (!VirtualProtect(pAddr, dwLen, PAGE_READWRITE, &dwOld))
        return false;

    memcpy(pData, pAddr, dwLen);
    return VirtualProtect(pAddr, dwLen, dwOld, &dwOld) != 0;
}

bool Patcher::PatchJmp(void* pAddr, void* pFunc, DWORD dwLen)
{
    return PatchType(INST_JMP, pAddr, pFunc, dwLen);
}

bool Patcher::PatchCall(void* pAddr, void* pFunc, DWORD dwLen)
{
    return PatchType(INST_CALL, pAddr, pFunc, dwLen);
}

bool Patcher::PatchNop(void* pAddr, DWORD dwLen)
{
    return PatchType(INST_NOP, pAddr, 0, dwLen);
}

bool Patcher::PatchType(BYTE bType, void* pAddr, void* pFunc, DWORD dwLen)
{
    BYTE* bCode = new BYTE[dwLen];
    memset(bCode, INST_NOP, dwLen);

    if (bType != INST_NOP)
    {
        DWORD dwFunc = (DWORD)pFunc - ((DWORD)pAddr + 5);
        bCode[0] = bType;
        *(DWORD*)&bCode[1] = dwFunc;
    }
    auto res = WriteBytes((LPVOID)pAddr, bCode, dwLen);
    delete bCode;
    return res;
}
