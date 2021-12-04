// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "RakNet.hpp"
#define EXTRA_INCLUDE_PART_RAKWEBSOCKET
#include "Extra/RakWebSocketAPI.hpp"
#undef EXTRA_INCLUDE_PART_RAKWEBSOCKET
class RakWebSocket {
#include "Extra/RakWebSocketAPI.hpp"
public:
    /*0*/ virtual ~RakWebSocket();
    /*1*/ virtual int /*enum WSConnectionResult*/ connect(std::string const&, std::vector<std::string> const&);
    /*2*/ virtual int /*enum WSConnectionResult*/ connect(std::string const&);
    /*3*/ virtual bool isReady() const;
    /*4*/ virtual void setOnMessageReceivedHandler(class std::function<void(class RakWebSocketDataFrame const&)> const&);
    /*5*/ virtual void setOnCloseHandler(class std::function<void(int /*enum CloseStatusCode*/, std::string const&)> const&);
    /*6*/ virtual void setOnConnectedHandler(class std::function<void(std::string const&)> const&);
    /*7*/ virtual void tick();
    /*8*/ virtual void _updateState()                 = 0;
    /*9*/ virtual unsigned int _genMaskingKey() const = 0;

protected:
    MCAPI void _close(enum CloseStatusCode);
    MCAPI void _createWebSocketKey();
    MCAPI void _fail(std::string const&, enum CloseStatusCode);
    MCAPI std::string _generateBase64SHA1Key(std::string const&);
    MCAPI void _processClosingHandshake(bool);
    MCAPI void _processDataFrames(class RakNet::BitStream&);
    MCAPI void _reset();
    MCAPI bool _sendControlFrame(unsigned char const*, unsigned __int64, enum OpCode);
    MCAPI bool _sendDataFrame(unsigned char const*, unsigned int, enum OpCode, bool);
    MCAPI bool _sendNonControlFrame(unsigned char const*, unsigned __int64, enum OpCode);
    MCAPI void _splitWebSocketURI(std::string const&, std::string&, std::string&, std::string&);
    MCAPI void _subProcessHttpResponse(class RakNet::BitStream&);
    MCAPI void _validateFields();
    MCAPI bool _validateWebSocketURI();
};