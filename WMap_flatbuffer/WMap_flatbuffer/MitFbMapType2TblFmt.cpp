#include "StdAfx.h"
#include "MitFbMapType2TblFmt.h"

using namespace MitMapType;


CMitFbMapType2TblFmt::CMitFbMapType2TblFmt(void)
{
    m_eMapType = MapType_MAP_ULT_MR3_TBL_FMT;
}


CMitFbMapType2TblFmt::~CMitFbMapType2TblFmt(void)
{
}

bool CMitFbMapType2TblFmt::Read(std::string strFilename)
{
    // add implementation
    // read / deserialize from file
    DWORD dwStart = GetTickCount();
    size_t size = deserialize(strFilename, m_fbBuf);

    if (size == 0)
    {
        // fail to read file
        return false;
    }

    // verify buffer content is valid
    if(!VerifyMapRootBuffer(flatbuffers::Verifier((const uint8_t*)m_fbBuf.get(), size)))
    {
        // invalid content
        return false;
    }

    // populate map info
    populateInfo();

    // get map matrix

    auto pRoot = GetMapRoot(m_fbBuf.get());

    // generate map matrix content

    if (pRoot->TblUlt2() == nullptr)
        return false;

    m_vecType2UnitInfo.clear();
    m_vecType2UnitInfo.reserve(pRoot->TblUlt2()->size());

    for (auto itUnit = pRoot->TblUlt2()->begin();
        itUnit != pRoot->TblUlt2()->end();
        ++itUnit)
    {
        std::vector<unsigned char> vecPnP;
        vecPnP.push_back(itUnit->pnp());

        //
        std::vector<short> vecPressure;
        vecPressure.push_back(itUnit->pickForce());
        vecPressure.push_back(itUnit->placeForce());
        vecPressure.push_back(itUnit->purgeForce());

        //
        std::vector<stXY> vecCoor;
        vecCoor.push_back(*itUnit->inwaferCoor());
        vecCoor.push_back(*itUnit->outwaferCoor());

        //
        m_vecType2UnitInfo.push_back(stFbType2UnitInfo(
                            itUnit->goodDie(),
                            itUnit->placedDie(),
                            itUnit->bincode(),
                            *itUnit->rejcode(),
                            itUnit->valid(),
                            vecPnP,
                            vecPressure,
                            vecCoor));

    }

    return true;
}

bool CMitFbMapType2TblFmt::Write(std::string strFilename)
{
    // add implementation

    auto vecFbUnits = m_builder.CreateVector(m_vecType2TblUnitInfo);

    // create flatbuffers for Map
    auto mitMap = CreateMapRoot(m_builder
                    , m_eMapType
                    , m_lotInfo
                    , m_waferInfo
                    , 0
                    , 0
                    , 0
                    , vecFbUnits
                    );

    // Finish building flatbuffer
    m_builder.Finish(mitMap);  // Serialize the root of the object.

    // save / serialize to file
    if (!serialize(strFilename, m_builder))
    {
        // fail to write file
        return false;
    }

    return true;
}

/// Type2 - using Table schema
void CMitFbMapType2TblFmt::AddType2TblUnit(const stFbType2UnitInfo &unit)
{
    m_vecType2TblUnitInfo.push_back(
        CreateTblUnitInfo2(m_builder,
                        unit.goodDie,
                        unit.placedDie,
                        unit.bincode,
                        &unit.rejcode,
                        unit.valid,
                        unit.vecPnP.empty() ? 0 : unit.vecPnP[0],
                        //
                        unit.vecPressureForce.empty() ? 0 : unit.vecPressureForce[0],
                        unit.vecPressureForce.empty() ? 0 : unit.vecPressureForce[1],
                        unit.vecPressureForce.empty() ? 0 : unit.vecPressureForce[2],
                        //
                        unit.vecWaferCoor.empty() ? &stXY() : &unit.vecWaferCoor[0],
                        unit.vecWaferCoor.empty() ? &stXY() : &unit.vecWaferCoor[1]));
}

void CMitFbMapType2TblFmt::GetType2TblUnits(std::vector<stFbType2UnitInfo> &vecUnits)
{
    vecUnits = m_vecType2UnitInfo;
}
