#pragma once

#include "..\..\schema\lotinfo_arm_generated.h"

#include <string>

class CFbLotInfoArm
{
public:
    CFbLotInfoArm(void);
    ~CFbLotInfoArm(void);

    bool Load(std::string strFilename);
    bool Save(std::string strFilename);

    bool serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb);
    bool deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf);

    bool GetArm(std::string strName, std::vector<lotinfo_arm::ARM> &vecArm);

};

