#include "../Public/memory.h"

uintptr_t memory::GetModuleBaseAddress(DWORD processId, const wchar_t* moduleName)
{
    uintptr_t moduleBaseAddress = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (snapshot != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 entry{};
        entry.dwSize = sizeof(MODULEENTRY32);

        if (Module32First(snapshot, &entry)) {
            do {
                if (!_wcsicmp(entry.szModule, moduleName)) {
                    moduleBaseAddress = (uintptr_t)entry.modBaseAddr;
                    break;
                }
            } while (Module32Next(snapshot, &entry));
        }
    }
    CloseHandle(snapshot);

    return moduleBaseAddress;
}

DWORD memory::GetProcessId(const wchar_t* processName)
{
    DWORD processId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(snapshot, &entry)) {
            do {
                if (!_wcsicmp(entry.szExeFile, processName)) {
                    processId = entry.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &entry));
        }
    }
    CloseHandle(snapshot);

    return processId;
}
