#include "minecraft/src-deps/core/utility/ReadOnlyBinaryStream.hpp"
#include "amethyst/Memory.h"

class BinaryStream : ReadOnlyBinaryStream {
public:
    void writeUnsignedVarInt(unsigned int data, char const* docName = nullptr, char const* docDesc = nullptr);
    void writeUnsignedVarInt64(unsigned __int64 data, char const* docName = nullptr, char const* docDesc = nullptr);
};