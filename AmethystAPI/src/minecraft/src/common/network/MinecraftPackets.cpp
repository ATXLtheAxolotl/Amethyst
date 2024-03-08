#include "minecraft/src/common/network/MinecraftPackets.hpp"
#include "MinecraftPackets.hpp"

std::shared_ptr<class Packet> MinecraftPackets::createPacket(int packetId) {
    std::shared_ptr<Packet> packet;
    
    using function = std::shared_ptr<Packet>(__fastcall*)(std::shared_ptr<Packet>, int);
    static auto func = reinterpret_cast<function>(SigScan("40 53 48 83 EC ? 45 33 C0 48 8B D9 FF CA 81 FA"));
    return func(packet, packetId);
}