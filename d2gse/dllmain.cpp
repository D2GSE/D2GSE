#include <Windows.h>
#include "d2gse.h"

int WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            Install();
            break;
        }
        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}
