// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Packet.hpp"
#define EXTRA_INCLUDE_PART_SETTINGSCOMMANDPACKET
#include "Extra/SettingsCommandPacketAPI.hpp"
#undef EXTRA_INCLUDE_PART_SETTINGSCOMMANDPACKET
class SettingsCommandPacket : public Packet {
#include "Extra/SettingsCommandPacketAPI.hpp"
public:
    /*0*/ virtual ~SettingsCommandPacket();
    /*1*/ virtual int /*enum MinecraftPacketIds*/ getId() const;
    /*2*/ virtual std::string getName() const;
    /*3*/ virtual void write(class BinaryStream&) const;
    /*5*/ virtual bool disallowBatching() const;
    /*6*/ virtual int /*enum StreamReadResult*/ _read(class ReadOnlyBinaryStream&);

public:
    MCAPI std::string const& getCommandString() const;
    MCAPI bool getSupressOutput() const;
};