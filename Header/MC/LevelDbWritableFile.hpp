// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_LEVELDBWRITABLEFILE
#include "Extra/LevelDbWritableFileAPI.hpp"
#undef EXTRA_INCLUDE_PART_LEVELDBWRITABLEFILE
class LevelDbWritableFile {
#include "Extra/LevelDbWritableFileAPI.hpp"
public:
    /*0*/ virtual ~LevelDbWritableFile();
    /*1*/ virtual class leveldb::Status Append(class leveldb::Slice const&);
    /*2*/ virtual class leveldb::Status Close();
    /*3*/ virtual class leveldb::Status Flush();
    /*4*/ virtual class leveldb::Status Sync();
};