#pragma once
#include <vector>
#include <memory>
#include "minecraft/src/common/world/level/block/components/BlockComponentBase.h"

namespace Bedrock {
    //template <typename T>
    using typeid_t = uint64_t;
}

class BlockComponentStorage {
public:
    /* this + 8  */ std::vector<std::pair<Bedrock::typeid_t, std::unique_ptr<BlockComponentBase>>> mComponents;
    /* this + 32 */ bool mAllowAddingComponents;
    /* this + 33 */ bool mAllowComponentReplacement;
    /* this + 34 */ bool mAllowTryGetComponentBeforeFinalization;

public:
    virtual ~BlockComponentStorage() = default;

    bool addingComponentsIsAllowed() {
        return mAllowAddingComponents;
    }

    void finalizeComponents() {
        mAllowAddingComponents = false;
    }

    void allowComponentReplacement() {
        mAllowComponentReplacement = true;
    }

    void allowTryGetComponentBeforeFinalization() {
        mAllowTryGetComponentBeforeFinalization = true;
    }
};

static_assert(sizeof(BlockComponentStorage) == 40);