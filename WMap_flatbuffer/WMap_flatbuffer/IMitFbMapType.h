#pragma once

#include <Windows.h>
#include "..\..\schema\mitMapType_generated.h"

#include <string>
#include <vector>

const std::string ULT_BINARY_MAP_FILE_EXT = _T(".fbu");

typedef struct _stFbLotInfo {

    std::string strMachineId;
    std::string strLotNum;
    std::string strRecipeName;
    std::string strPackageName;
    std::string strShift;
    std::string strOperator;

    _stFbLotInfo()
    {
    };
}stFbLotInfo;

typedef struct _stFbWaferInfo {
    MitMapType::stfXY dieSize;
    MitMapType::stfXY dieGap;
    MitMapType::stXY maxRowCol;
    short shNotch;
    std::vector<MitMapType::stXY>  targetDie;

    std::string strWaferId;

    float fWaferSize;
    float edgeClearance;
    short pickDegree;

    _stFbWaferInfo()
        : fWaferSize (200.0)
        , shNotch (0)
        , edgeClearance (5.0)
        , pickDegree (0)
    {
    };
} stFbWaferInfo;

typedef struct _stFbType2UnitInfo {

    long goodDie;
    long placedDie;
    short bincode;

    MitMapType::stRejCode rejcode;

    bool valid;
    std::vector<unsigned char> vecPnP;
    std::vector<short> vecPressureForce;
    std::vector<MitMapType::stXY> vecWaferCoor;

    _stFbType2UnitInfo(long _goodDie,
                        long _placedDie,
                        short _bincode,
                        MitMapType::stRejCode _rejcode,
                        bool  _valid,
                        std::vector<unsigned char> &_vecPnP,
                        std::vector<short> &_vecPressureForce,
                        std::vector<MitMapType::stXY> &_vecWaferCoor)
        : goodDie  (_goodDie)
        , placedDie(_placedDie)
        , bincode  (_bincode)

        , rejcode  (_rejcode)

        , valid    (_valid)

        , vecPnP    (_vecPnP)
        , vecPressureForce(_vecPressureForce)
        , vecWaferCoor(_vecWaferCoor)
    {
    };
} stFbType2UnitInfo;

class CIMitFbMapType 
{
public:
    CIMitFbMapType(void);
    virtual ~CIMitFbMapType(void);

    virtual bool Read(std::string strFilename) = 0;
    virtual bool Write(std::string strFilename) = 0;

    //
    virtual void StartBuild(size_t size);

    virtual void AddLotInfo();
    virtual void AddWaferInfo();

    MitMapType::MapType GetMapType() { return m_eMapType; };

    virtual void AddUnit(const MitMapType::stUnitInfo &unit) { return; };
    virtual void AddUnits(const std::vector<MitMapType::stUnitInfo> &vecUnits) { return; };
    virtual void GetUnits(std::vector<MitMapType::stUnitInfo> &vecUnits) { return; };
    
    virtual void AddType2TblUnit(const stFbType2UnitInfo &unit) { return; };
    virtual void GetType2TblUnits(std::vector<stFbType2UnitInfo> &vecUnits) { return; };

    virtual void AddType2Unit(const stFbType2UnitInfo &unit) { return; };
    virtual void GetType2Units(std::vector<MitMapType::stUnitInfo2> &vecUnits) { return; };

    stFbLotInfo & LotData();
    stFbWaferInfo & WaferData();

protected:
    bool serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb);
    size_t deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf);

    virtual void populateInfo();
 
    flatbuffers::FlatBufferBuilder                  m_builder;
    flatbuffers::Offset<MitMapType::TblLotInfo>     m_lotInfo;
    flatbuffers::Offset<MitMapType::TblWaferInfo>   m_waferInfo;
    flatbuffers::Offset<flatbuffers::Vector<const MitMapType::stUnitInfo *>>     m_vecFbUnits;

    std::vector<flatbuffers::Offset<MitMapType::TblUnitInfo2>>   m_vecType2TblUnitInfo;

    // Type1
    std::vector<MitMapType::stUnitInfo>             m_vecUnits;
    // Type2
    std::vector<stFbType2UnitInfo>                  m_vecType2UnitInfo;
    std::vector<MitMapType::stUnitInfo2>             m_vecType2Units;

    std::unique_ptr<char> m_fbBuf;

    MitMapType::MapType m_eMapType;

private:
    //

    stFbLotInfo    m_stLotData;
    stFbWaferInfo  m_stWaferData;

};

