#include "minecraft/src-deps/core/utility/ReadOnlyBinaryStream.hpp"

byte ReadOnlyBinaryStream::getByte() {
    byte value;
    using function = byte(__thiscall*)(ReadOnlyBinaryStream*, byte);
    static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 48 89 7C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B DA 48 89 54 24 ? 33 FF 40 88 7D ? 48 8B 01 44 8D 4F ? 4C 8D 45 ? 48 8D 54 24 ? 48 8B 40 ? FF 15 ? ? ? ? 48 8B D0 48 8D 4D ? E8 ? ? ? ? 40 38 7D ? 75 ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 40 38 7D ? 0F 85 ? ? ? ? 0F 10 05 ? ? ? ? 0F 11 44 24 ? F2 0F 10 0D ? ? ? ? F2 0F 11 4C 24 ? C6 45 ? ? 48 8B 55 ? 48 3B 55 ? 74 ? 0F 11 02 F2 0F 11 4A ? C6 42 ? ? 80 7D ? ? 74 ? 0F 57 C0 0F 11 42 ? 48 89 7A ? 48 89 7A ? 0F 10 44 24 ? 0F 11 42 ? 0F 10 4C 24 ? 0F 11 4A ? 66 0F 6F 05 ? ? ? ? F3 0F 7F 44 24 ? C6 44 24 ? ? 48 8B 44 24 ? 48 89 42 ? 48 8B 45 ? 48 89 42 ? C6 42 ? ? 48 83 45 ? ? EB ? 4C 8D 44 24 ? 48 8D 4D ? E8 ? ? ? ? 80 7D ? ? 74 ? 48 8D 4C 24 ? E8 ? ? ? ? 90 0F 28 45 ? 0F 11 45 ? 48 8B 55 ? 48 89 7D ? 48 8B 4D ? 48 89 7D ? 48 8B 45 ? 48 89 7D ? 48 89 45 ? 48 89 4D ? 48 89 55 ? 48 8B 55 ? 48 89 7D ? 48 8B 4D ? 48 89 7D ? 48 8B 45 ? 48 89 7D ? 48 89 45 ? 48 89 4D ? 48 89 55 ? 48 8D 55 ? 48 8B CB E8 ? ? ? ? 80 7D ? ? 75 ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? EB ? C6 43 ? ? 0F B6 45 ? 88 03 48 8B C3 48 8B 4D ? 48 33 CC E8 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 7B ? 49 8B E3 5D C3 CC CC CC CC CC CC 0F B6 42"));
    return func(this, value);
}

int ReadOnlyBinaryStream::getVarInt() {
    int value;
    using function = int(__thiscall*)(ReadOnlyBinaryStream*, int);
    static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 48 89 7C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B DA 48 89 54 24 ? 33 FF 48 8D 54 24 ? E8 ? ? ? ? 48 8B D0 48 8D 4D ? E8 ? ? ? ? 40 38 7C 24 ? 75 ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 40 38 7D ? 0F 85 ? ? ? ? 0F 10 05 ? ? ? ? 0F 11 44 24 ? F2 0F 10 0D ? ? ? ? F2 0F 11 4C 24 ? C6 44 24 ? ? 48 8B 55 ? 48 3B 55 ? 74 ? 0F 11 02 F2 0F 11 4A ? C6 42 ? ? 80 7C 24 ? ? 74 ? 0F 57 C0 0F 11 42 ? 48 89 7A ? 48 89 7A ? 0F 10 44 24 ? 0F 11 42 ? 0F 10 4C 24 ? 0F 11 4A ? 66 0F 6F 05 ? ? ? ? F3 0F 7F 44 24 ? C6 44 24 ? ? 48 8B 44 24 ? 48 89 42 ? 48 8B 44 24 ? 48 89 42 ? C6 42 ? ? 48 83 45 ? ? EB ? 4C 8D 44 24 ? 48 8D 4D ? E8 ? ? ? ? 80 7C 24 ? ? 74 ? 48 8D 4C 24 ? E8 ? ? ? ? 90 0F 28 45 ? 0F 11 45 ? 48 8B 55 ? 48 89 7D ? 48 8B 4D ? 48 89 7D ? 48 8B 45 ? 48 89 7D ? 48 89 45 ? 48 89 4D ? 48 89 55 ? 48 8B 55 ? 48 89 7D ? 48 8B 4D ? 48 89 7D ? 48 8B 45 ? 48 89 7D ? 48 89 45 ? 48 89 4D ? 48 89 55 ? 48 8D 55 ? 48 8B CB E8 ? ? ? ? 80 7D ? ? 75 ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? EB ? 8B 45"));
    return func(this, value);
}

uint32_t ReadOnlyBinaryStream::getUnsignedVarInt() {
    uint32_t value;
    using function = uint32_t(__thiscall*)(ReadOnlyBinaryStream*, uint32_t);
    static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 55 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B F2 4C 8B F1 48 89 54 24 ? 45 33 FF 41 8B FF 41 8B DF 66 0F 1F 44 00 ? 48 8D 54 24 ? 49 8B CE E8 ? ? ? ? 48 8B D0 48 8D 4D ? E8 ? ? ? ? 44 38 7C 24 ? 75 ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 44 38 7D ? 74 ? 44 0F B6 45 ? 41 8B D0 83 E2 ? 8B CB D3 E2"));
    return func(this, value);
}