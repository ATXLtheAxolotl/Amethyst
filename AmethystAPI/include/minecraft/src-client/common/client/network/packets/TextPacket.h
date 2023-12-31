#include "minecraft/src-client/common/client/network/Packet.h"
#include "amethyst/Memory.h"

class TextPacket : public Packet {
public:
    enum TextType : unsigned __int8 {
        Raw,
        Chat,
        Translate,
        Popup,
        JukeboxPopup,
        Tip,
        SystemMessage,
        Whisper,
        Announcement,
        TextObject
    };

	TextType textType;

private:
	bool gap[7];

public:
	std::string sourceName;           
	std::string message;

private:
	bool gap2[24];

public:
	bool translationNeeded = false;

private:
	bool gap3[7];

public:
	std::string xboxUserId;
	std::string platformChatId;
};