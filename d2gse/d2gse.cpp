#include "d2gse.h"
#include "Patcher.h"
#define _DEFINE_VARS
#include "Ptrs.h"
#include "hooks.h"
#include "CommandHandler.h"
#include "Helpers.h"

void __fastcall AfterInitialize()
{
    Patcher::PatchCall(p_D2Server_OldPacketFunc_patchloc, MyHandlePacket_stub, 6);

    Patcher::PatchJmp(p_D2GS_D2GSGameListInsert_Patchloc, D2GSGameListInsertHook_STUB, 10);
    Patcher::PatchJmp(p_D2GS_D2GSGameListDelete_Patchloc, D2GSGameListDeleteHook_STUB, 5);

    sCommandHandler.Install();
    D2GSE_EventLog("System successfully initialized");
}

void Install()
{
    DefineOffsets();

    Patcher::PatchCall(p_D2Server_AfterInitialize, AfterInitialize, 6);
}
