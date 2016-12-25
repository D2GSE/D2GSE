#include "d2gse.h"
#include "Patcher.h"
#define _DEFINE_VARS
#include "Ptrs.h"
#include "hooks.h"

void __fastcall AfterInitialize()
{
    Patcher::PatchCall(p_D2Server_OldPacketFunc_patchloc, MyHandlePacket_stub, 6);
}

void Install()
{
    DefineOffsets();

    Patcher::PatchCall(p_D2Server_AfterInitialize, AfterInitialize, 6);
}
