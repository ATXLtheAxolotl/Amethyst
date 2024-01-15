class Packet;

class LoopbackPacketSender {
public:
    typedef void(__thiscall* _sendToServer)(LoopbackPacketSender*, Packet*);
    void sendToServer(Packet* packet);
};