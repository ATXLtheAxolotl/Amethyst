#include "minecraft/src-client/common/client/network/LoopbackPacketSender.h"
#include "amethyst/Memory.h"

void LoopbackPacketSender::sendToServer(Packet* packet) {
    using function = void(__thiscall*)(LoopbackPacketSender*, Packet*);
    static auto func = reinterpret_cast<function>(SigScan("40 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 0F B6 41"));
    return func(this, packet);
}