// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Packet.hpp"
#define EXTRA_INCLUDE_PART_TEXTPACKET
#include "Extra/TextPacketAPI.hpp"
#undef EXTRA_INCLUDE_PART_TEXTPACKET
class TextPacket : public Packet {
#include "Extra/TextPacketAPI.hpp"
public:
    /*0*/ virtual ~TextPacket();
    /*1*/ virtual int /*enum MinecraftPacketIds*/ getId() const;
    /*2*/ virtual std::string getName() const;
    /*3*/ virtual void write(class BinaryStream&) const;
    /*5*/ virtual bool disallowBatching() const;
    /*6*/ virtual int /*enum StreamReadResult*/ _read(class ReadOnlyBinaryStream&);

public:
    MCAPI static class TextPacket createAnnouncement(std::string const&, std::string const&, std::string const&, std::string const&);
    MCAPI static class TextPacket createChat(std::string const&, std::string const&, std::string const&, std::string const&);
    MCAPI static class TextPacket createJukeboxPopup(std::string const&, std::vector<std::string> const&);
    MCAPI static class TextPacket createSystemMessage(std::string const&);
    MCAPI static class TextPacket createTextObjectMessage(class ResolvedTextObject const&, std::string, std::string);
    MCAPI static class TextPacket createTextObjectWhisperMessage(class ResolvedTextObject const&, std::string const&, std::string const&);
    MCAPI static class TextPacket createTranslated(std::string const&, std::vector<std::string> const&);
    MCAPI static class TextPacket createTranslatedAnnouncement(std::string const&, std::string const&, std::string const&, std::string const&);
    MCAPI static class TextPacket createWhisper(std::string const&, std::string const&, std::string const&, std::string const&);
};