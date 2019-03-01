#pragma once

#include "IMitFbMapType.h"

#include <string>
#include <vector>


class CMitFbMapType1 : public CIMitFbMapType
{
public:
    CMitFbMapType1(void);
    ~CMitFbMapType1(void);

    bool Read(std::string strFilename)  override;
    bool Write(std::string strFilename) override;

    void AddUnit(const MitMapType::stUnitInfo &unit) override;
    void AddUnits(const std::vector<MitMapType::stUnitInfo> &vecUnits) override;
    void GetUnits(std::vector<MitMapType::stUnitInfo> &vecUnits) override;

};

