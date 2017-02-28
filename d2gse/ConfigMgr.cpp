#include "ConfigMgr.h"
#include "Ptrs.h"
#include <assert.h>
#include "Patcher.h"

void ConfigMgr::Initialize()
{
    if (!Entries.empty())
        return;

    Entries.resize(CONFIG_MAX + 1);

    assert(CONFIG_COUNT_DEFAULT <= CONFIG_MAX);

    memcpy(Entries.data(), p_D2GS_D2GSConfig, CONFIG_COUNT_DEFAULT * sizeof(D2GSConfigEntry));

    FillCustomEntries();

    auto newAddr = Entries.data();
    Patcher::WriteBytes((void*)((DWORD)p_D2GS_Config_PatchLoc + 1), &newAddr, 4);

    D2GS_D2GSReadConfig();
}

void ConfigMgr::FillCustomEntries()
{
    D2GSConfigEntry& WEMotdEntry = Entries[WEMotd];
    WEMotdEntry.Entry = "WEMotd";
    WEMotdEntry.ConfigType = ConfigType::String;
    WEMotdEntry.Default = "";
    WEMotdEntry.Data = new char[256];
}
