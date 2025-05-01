#include <Windows.h>
#include <MinHook/MinHook.h>
#include <iostream>

static const std::string target = "sm.gui.chatMessage( \"#{CHALLENGE_BUILDER_SAVE_REMINDER}\" )";

extern "C" int(*pluaL_loadbuffer)(LPVOID L, const char* buff, size_t sz, const char* name) = 0;
extern "C" int hluaL_loadbuffer(LPVOID L, const char* buff, size_t sz, const char* name) {
    // Check if its the file we want
    if (strcmp(name, "...GE_DATA/Scripts/challenge/ChallengeGame.lua") != 0)
        return pluaL_loadbuffer(L, buff, sz, name);

    std::string modifiedBuff(buff, sz);

    // Find the "target" containing our pesky save reminder lua code. Just incase also check if
    // pos isnt npos. (If so then don't continue)
    const size_t pos = modifiedBuff.find(target);
    if (pos == std::string::npos)
        return pluaL_loadbuffer(L, buff, sz, name);

    // Replace it with spaces meaning it wouldn't show the chat message no more.
    const size_t targetSize = target.size();
    modifiedBuff.replace(pos, targetSize, targetSize, ' ');

    // Call the original function but with the modified buffer instead of the original. Meaning that
    // the user won't get spammed with it.
    return pluaL_loadbuffer(L, modifiedBuff.c_str(), modifiedBuff.size(), name);
}

void Attach() {
    // Initialize minhook, hook & enable luaL_loadbuffer
    // luaL_loadbuffer gets executed by the
    MH_Initialize();
    MH_CreateHookApi(L"lua51.dll", "luaL_loadbuffer", hluaL_loadbuffer, reinterpret_cast<LPVOID*>(&pluaL_loadbuffer));
    MH_EnableHook(MH_ALL_HOOKS);
}

void Detach() {
    // Deinitialize minhook
    MH_Uninitialize();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        Attach();
        break;
    case DLL_PROCESS_DETACH:
        Detach();
        break;
    }

    return TRUE;
}