#pragma once

#include "IMitFbMapType.h"

#include <string>

class CMitFbMapType2TblFmt : public CIMitFbMapType
{
public:
    CMitFbMapType2TblFmt(void);
    ~CMitFbMapType2TblFmt(void);

    bool Read(std::string strFilename)  override;
    bool Write(std::string strFilename) override;

    void AddType2TblUnit(const stFbType2UnitInfo &unit) override;
    void GetType2TblUnits(std::vector<stFbType2UnitInfo> &vecUnits) override;
};

