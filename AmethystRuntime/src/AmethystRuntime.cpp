#include "AmethystRuntime.h"

std::vector<ModInitializeHooks> gModInitialize;
std::vector<ModPacketSend> gModPacketSend;
std::vector<ModTick> gModTick;
std::vector<ModStartJoinGame> gModStartJoin;
std::vector<ModShutdown> gModShutdown;
std::vector<ModRender> gModRender;

Config AmethystRuntime::ReadConfig() {
    // Ensure it exist
    std::string configPath = GetAmethystUWPFolder() + "launcher_config.json";

    if (!fs::exists(configPath)) {
        Log::Error("[AmethystRuntime] Could not find launcher_config.json\n\tat '{}'", configPath);
        throw std::exception();
    }

    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        Log::Error("[AmethystRuntime] Failed to open launcher_config.json\n\tat '{}'", configPath);
        throw std::exception();
    }

    // Read into a std::string
    std::stringstream buffer;
    buffer << configFile.rdbuf();
    configFile.close();
    std::string fileContents = buffer.str();

    return Config(fileContents);
}

void AmethystRuntime::LoadMods() {
    // Initialize MinHook
    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) {
        Log::Error("MH_Initialize failed! Reason: {}", MH_StatusToString(status));
        throw std::exception("MH_Initialize failed!");
    }

    // Read config.json file
    Config config = ReadConfig();
    for (auto& modName : config.mods) {
        this->m_mods.push_back(Mod(modName));
    }

    if (config.promptDebugger) AttachDebugger();

    // Load functions from the mods
    for (auto& mod : m_mods) {
        FARPROC addr;

        addr = mod.GetFunction("Initialize");
        if (addr != NULL) {
            gModInitialize.push_back(reinterpret_cast<ModInitializeHooks>(addr));
        }

        addr = mod.GetFunction("OnPacketSend");
        if (addr != NULL) {
            gModPacketSend.push_back(reinterpret_cast<ModPacketSend>(addr));
        }

        addr = mod.GetFunction("OnTick");
        if (addr != NULL) {
            gModTick.push_back(reinterpret_cast<ModTick>(addr));
        }

        addr = mod.GetFunction("OnStartJoinGame");
        if (addr != NULL) {
            gModStartJoin.push_back(reinterpret_cast<ModStartJoinGame>(addr));
        }

        addr = mod.GetFunction("OnRenderUI");
        if (addr != NULL) {
            gModRender.push_back(reinterpret_cast<ModRender>(addr));
        }

        addr = mod.GetFunction("Shutdown");
        if (addr != NULL) {
            gModShutdown.push_back(reinterpret_cast<ModShutdown>(addr));
        } else {
            Log::Warning("[AmethystRuntime] '{}' does not have 'void Shutdown()'. A mod should remove all hooks here for hot-reloading to work.", mod.modName);
        }

        Log::Info("[AmethystRuntime] Loaded '{}'", mod.modName);
    }
}

void AmethystRuntime::RunMods() {
    // AmethystRuntime's own Hooks
    InitializeHooks();

    Config config = ReadConfig();

    // Allow mods to create hooks
    for (auto& init_func : gModInitialize)
        init_func(config.gameVersion.c_str());

    while (true) {
        Sleep(1000 / 20);
        if (GetAsyncKeyState(VK_NUMPAD0)) break;

        if (GetAsyncKeyState('R') & 0x8000) {
            Log::Info("\n========================= Beginning hot-reload! =========================");
            this->Shutdown();
            this->LoadMods();

            Sleep(100);
            return this->RunMods();
        }
    }
}

// Hooks
ScreenView::_setupAndRender _ScreenView_setupAndRender;
static void* ScreenView_setupAndRender(ScreenView* self, UIRenderContext* ctx) {
    for (auto& render_func : gModRender)
        render_func(self, ctx);
    return _ScreenView_setupAndRender(self, ctx);
}

ClientInstance::_onStartJoinGame _ClientInstance_onStartJoinGame;
static int64_t ClientInstance_onStartJoinGame(ClientInstance* self, int64_t a2, int64_t a3, uint64_t a4) {
    for (auto& start_func : gModStartJoin)
        start_func(self);
    return _ClientInstance_onStartJoinGame(self, a2, a3, a4);
}

LoopbackPacketSender::_sendToServer _LoopbackPacketSender_sendToServer;
static void LoopbackPacketSender_sendToServer(LoopbackPacketSender* self, Packet* packet) {
    for (auto& sendFunc : gModPacketSend)
        sendFunc(self, packet);

    return _LoopbackPacketSender_sendToServer(self, packet);
}

Level::_tickEntities _Level_tickEntities;
static void Level_tickEntities(Level* self) {
    for (auto& tickFunc : gModTick)
        tickFunc();

    return _Level_tickEntities(self);
}

void AmethystRuntime::InitializeHooks() {
    g_hookManager.CreateHook(
        SigScan("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 89 54 24 ? 4C 8B E9 48 89 4C 24"),
        &ScreenView_setupAndRender, reinterpret_cast<void**>(&_ScreenView_setupAndRender));

    g_hookManager.CreateHook(
        SigScan("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 45 8B F1"),
        &ClientInstance_onStartJoinGame, reinterpret_cast<void**>(&_ClientInstance_onStartJoinGame));

    g_hookManager.CreateHook(
        SigScan("40 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 0F B6 41"),
        &LoopbackPacketSender_sendToServer, reinterpret_cast<void**>(&_LoopbackPacketSender_sendToServer));

    g_hookManager.CreateHook(
        SigScan("48 89 5C 24 ? 57 48 83 EC ? 48 8B B9 ? ? ? ? 48 8B 1F 48 3B DF 74 1F"),
        &Level_tickEntities, reinterpret_cast<void**>(&_Level_tickEntities));
}

void AmethystRuntime::Shutdown() {
    g_hookManager.Shutdown();

    // Allow each mod to have its shutdown logic
    for (auto& shutdown_func : gModShutdown)
        shutdown_func();

    // Unload each mod dll from game memory
    for (auto& mod : m_mods) {
        mod.Free();
    }

    // Remove any existing function addresses to mod funcs
    m_mods.clear();
    gModInitialize.clear();
    gModTick.clear();
    gModStartJoin.clear();
    gModShutdown.clear();
    gModRender.clear();

    // Disable MH and remove any created hooks
    MH_Uninitialize();
}

void AmethystRuntime::AttachDebugger() {
    std::string command = fmt::format("vsjitdebugger -p {:d}", GetCurrentProcessId());
    system(command.c_str());
}