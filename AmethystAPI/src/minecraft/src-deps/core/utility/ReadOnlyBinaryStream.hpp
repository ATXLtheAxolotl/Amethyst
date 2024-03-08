#include "amethyst/Memory.h"
#include <stdint.h>

class ReadOnlyBinaryStream {
public:
    uint8_t getByte();
    int getVarInt();
    uint32_t getUnsignedVarInt();
};