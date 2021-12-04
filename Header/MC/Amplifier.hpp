// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_AMPLIFIER
#include "Extra/AmplifierAPI.hpp"
#undef EXTRA_INCLUDE_PART_AMPLIFIER
class Amplifier {
#include "Extra/AmplifierAPI.hpp"
public:
    /*0*/ virtual ~Amplifier();
    /*1*/ virtual float getAmount(int, float) const;
    /*2*/ virtual bool shouldBuff(int, int) const;
    /*3*/ virtual int getTickInterval(int) const;
};