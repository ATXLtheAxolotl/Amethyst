#include <cstdint>
#include <string>

class Packet {
private:
    uintptr_t** vtable;
    bool padding[0x28];
};