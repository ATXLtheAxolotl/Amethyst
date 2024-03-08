#pragma once
#include "amethyst/Memory.h"
#include <memory>

class MinecraftPackets {
public:
    //40 53 48 83 EC ? 45 33 C0 48 8B D9 FF CA 81 FA
    static std::shared_ptr<class Packet> createPacket(int);
};