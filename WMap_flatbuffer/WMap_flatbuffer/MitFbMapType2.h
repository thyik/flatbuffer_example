#pragma once

#include "IMitFbMapType.h"

#include <string>

class CMitFbMapType2 : public CIMitFbMapType
{
public:
    CMitFbMapType2(void);
    ~CMitFbMapType2(void);

    bool Read(std::string strFilename)  override;
    bool Write(std::string strFilename) override;

    void AddType2Unit(const stFbType2UnitInfo &unit) override;
    void GetType2Units(std::vector<MitMapType::stUnitInfo2> &vecUnits) override;

};

