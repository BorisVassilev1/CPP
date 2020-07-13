#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <psapi.h>

// To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS
// and compile with -DPSAPI_VERSION=1


size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof( memCounter ));

    SIZE_T physMemUsedByMe = memCounter.WorkingSetSize;
    return physMemUsedByMe;
}

int main()
{
    PROCESS_MEMORY_COUNTERS memCounter;
    BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof( memCounter ));

    //PROCESS_MEMORY_COUNTERS_EX pmc;
    //GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    SIZE_T physMemUsedByMe = memCounter.WorkingSetSize / 1024;

    std::cout << physMemUsedByMe;


    system("pause");

    return 0;
}
