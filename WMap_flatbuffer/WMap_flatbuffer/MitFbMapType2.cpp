#include "StdAfx.h"
#include "MitFbMapType2.h"

#include "windows.h"

using namespace MitMapType;


CMitFbMapType2::CMitFbMapType2(void)
{
    m_eMapType = MapType_MAP_ULT_MR3;
}


CMitFbMapType2::~CMitFbMapType2(void)
{
}

bool CMitFbMapType2::Read(std::string strFilename)
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
    if (pRoot->ult2() == nullptr)
        return false;

    m_vecType2Units.clear();
    m_vecType2Units.reserve(pRoot->ult2()->size());

    for (auto itUnit = pRoot->ult2()->begin();
        itUnit != pRoot->ult2()->end();
        ++itUnit)
    {
        m_vecType2Units.push_back(**itUnit);
    }
    return true;
}

bool CMitFbMapType2::Write(std::string strFilename)
{
    // add implementation

    auto vecFbUnits = m_builder.CreateVectorOfStructs(m_vecType2Units);

    // create flatbuffers for Map
    auto mitMap = CreateMapRoot(m_builder
                    , m_eMapType
                    , m_lotInfo
                    , m_waferInfo
                    , 0
                    , 0
                    , vecFbUnits
                    , 0);

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

/// Type2 - using struct schema
//
void CMitFbMapType2::AddType2Unit(const stFbType2UnitInfo &unit)
{
    m_vecType2Units.push_back(stUnitInfo2(
                        unit.goodDie,
                        unit.placedDie,
                        unit.bincode,
                        unit.rejcode,
                        unit.valid,

                        0,
                        
                        0,
                        0,
                        0,

                        stXY(0,0),
                        stXY(0,0)));
}

void CMitFbMapType2::GetType2Units(std::vector<MitMapType::stUnitInfo2> &vecUnits)
{
    vecUnits = m_vecType2Units;
}