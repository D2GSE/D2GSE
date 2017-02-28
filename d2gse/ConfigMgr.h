#pragma once

#include <vector>
#include "Structs.h"

class ConfigMgr
{
    static const int SizeReserve = 100;
    std::vector<D2GSConfigEntry> Entries;

    ConfigMgr()
    {
        Entries.reserve(SizeReserve);
    }

    void FillCustomEntries();

public:
    static ConfigMgr& instance()
    {
        static ConfigMgr config;
        return config;
    }

    void Initialize();

    D2GSConfigEntry const* GetEntry(int Index) const
    {
        if (Index >= CONFIG_MAX)
            return nullptr;

        return &Entries[Index];
    }
};

#define sConfigMgr ConfigMgr::instance()
