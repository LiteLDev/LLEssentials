// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_TESTFORBLOCKSCOMMAND
#include "Extra/TestForBlocksCommandAPI.hpp"
#undef EXTRA_INCLUDE_PART_TESTFORBLOCKSCOMMAND
class TestForBlocksCommand {
#include "Extra/TestForBlocksCommandAPI.hpp"
public:
    /*0*/ virtual ~TestForBlocksCommand();
    /*1*/ virtual void execute(class CommandOrigin const&, class CommandOutput&) const;

public:
    MCAPI static void setup(class CommandRegistry&);
};