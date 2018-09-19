#pragma once

#include <string>

class CFbLotInfoArm
{
public:
    CFbLotInfoArm(void);
    ~CFbLotInfoArm(void);

    bool Load(std::string strFilename);
    bool Save(std::string strFilename);

};

