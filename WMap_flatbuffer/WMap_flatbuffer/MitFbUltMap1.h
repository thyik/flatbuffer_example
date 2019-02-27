#pragma once

#include "..\..\schema\mitMapType_generated.h"

#include <string>
#include <vector>

typedef struct _stLotInfo {

    std::string strMachineId;
    std::string strLotNum;
    std::string strRecipeName;
    std::string strPackageName;
    std::string strShift;
    std::string strOperator;

    _stLotInfo()
    {
    };
}stLotInfo;

typedef struct _stWaferInfo {
    MitMapType::stfXY dieSize;
    MitMapType::stfXY dieGap;
    MitMapType::stXY maxRowCol;
    short shNotch;
    std::vector<MitMapType::stXY>  targetDie;

    std::string strWaferId;

    float fWaferSize;

    _stWaferInfo()
    {
    };
} stWaferInfo;

class CMitFbUltMap1 //: public CUltMapBase
{
public:
    CMitFbUltMap1(void);
    ~CMitFbUltMap1(void);

    bool Read(std::string strFilename);
    bool Write(std::string strFilename);

    //
    void StartBuild(size_t size);
    void AddLotInfo();
    void AddWaferInfo();
    void AddUnit(const MitMapType::stUnitInfo &unit);
    void AddUnits(const std::vector<MitMapType::stUnitInfo> &vecUnits);

    stLotInfo & LotData();
    stWaferInfo & WaferData();
    void GetUnits(std::vector<MitMapType::stUnitInfo> &vecUnits);

private:
    bool serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb);
    size_t deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf);

    void populateInfo();

    //
    flatbuffers::FlatBufferBuilder                  m_builder;
    flatbuffers::Offset<MitMapType::TblLotInfo>     m_lotInfo;
    flatbuffers::Offset<MitMapType::TblWaferInfo>   m_waferInfo;
    std::vector<MitMapType::stUnitInfo>             m_vecUnits;

    std::unique_ptr<char> m_fbBuf;

    stLotInfo  m_stLotData;
    stWaferInfo  m_stWaferData;

};

