#pragma once

#include "minecraft/src/common/SharedPtr.hpp"
#include <memory>
#include <minecraft/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <minecraft/src/common/world/level/ILevel.hpp>
#include <minecraft/src/common/world/level/BlockSourceListener.hpp>
#include <minecraft/src/common/world/level/IWorldRegistriesProvider.hpp>

class BlockTypeRegistry;
class PacketSender;

class Level : public ILevel, public BlockSourceListener, public IWorldRegistriesProvider {
public:
    /* this + 40   */ std::byte padding40[800];
    /* this + 840  */ const ItemRegistryRef mItemRegistry;
    /* this + 856  */ std::byte padding856[2008];
    /* this + 2864 */ PacketSender* mPacketSender;
    /* this + 2872 */ std::byte padding2872[2648];
    /* this + 5520 */ bool isClientSide;
};

// 1.21.0.3
static_assert(offsetof(Level, mPacketSender) == 2864);
static_assert(offsetof(Level, isClientSide) == 5520);