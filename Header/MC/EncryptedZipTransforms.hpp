// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#define EXTRA_INCLUDE_PART_ENCRYPTEDZIPTRANSFORMS
#include "Extra/EncryptedZipTransformsAPI.hpp"
#undef EXTRA_INCLUDE_PART_ENCRYPTEDZIPTRANSFORMS
class EncryptedZipTransforms {
#include "Extra/EncryptedZipTransformsAPI.hpp"
public:
    /*0*/ virtual ~EncryptedZipTransforms();
    /*1*/ virtual bool readTransform(std::vector<unsigned char>&) const;
    /*2*/ virtual bool writeTransform(std::vector<unsigned char>&) const;
};