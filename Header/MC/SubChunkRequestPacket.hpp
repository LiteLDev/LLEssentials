// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Packet.hpp"
#define EXTRA_INCLUDE_PART_SUBCHUNKREQUESTPACKET
#include "Extra/SubChunkRequestPacketAPI.hpp"
#undef EXTRA_INCLUDE_PART_SUBCHUNKREQUESTPACKET
class SubChunkRequestPacket : public Packet {
#include "Extra/SubChunkRequestPacketAPI.hpp"
public:
    /*0*/ virtual ~SubChunkRequestPacket();
    /*1*/ virtual int /*enum MinecraftPacketIds*/ getId() const;
    /*2*/ virtual std::string getName() const;
    /*3*/ virtual void write(class BinaryStream&) const;
    /*5*/ virtual bool disallowBatching() const;
    /*6*/ virtual int /*enum StreamReadResult*/ _read(class ReadOnlyBinaryStream&);
};