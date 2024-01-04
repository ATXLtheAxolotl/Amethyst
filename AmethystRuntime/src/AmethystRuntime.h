#pragma once
#include "MinHook.h"
#include "Utils.h"
#include "Mod.h"

#include "minecraft/src-client/common/client/network/LoopbackPacketSender.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/network/Packet.h"
#include "minecraft/src-client/common/client/gui/ScreenView.h"
#include "minecraft/src/common/Minecraft.h"

#include "amethyst/HookManager.h"
#include "amethyst/Config.h"

#include <fstream>
#include <sstream>
#include <vector>

typedef void (*ModPacketSend)(LoopbackPacketSender* packetSender, Packet* packet);
typedef void (*ModRender)(ScreenView* screenView, UIRenderContext* ctx);
typedef void (*ModStartJoinGame)(ClientInstance* clientInstance);
typedef void (*ModInitializeHooks)(const char* gameVersion);
typedef bool (*ModTickBefore)();
typedef void (*ModTickAfter)();
typedef void (*ModShutdown)();

class AmethystRuntime {
private:
    std::vector<Mod> m_mods;

public:
    void InitializeHooks();
    void LoadMods();
    void RunMods();
    void Shutdown();

private:
    Config ReadConfig();
    void AttachDebugger();
};

extern AmethystRuntime g_runtime;
extern HookManager g_hookManager;