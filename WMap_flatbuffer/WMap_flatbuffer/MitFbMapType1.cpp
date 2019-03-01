#include "StdAfx.h"
#include "MitFbMapType1.h"

using namespace MitMapType;

CMitFbMapType1::CMitFbMapType1(void)
{
    m_eMapType = MapType_MAP_ULT_C330;
}


CMitFbMapType1::~CMitFbMapType1(void)
{
    
}

bool CMitFbMapType1::Read(std::string strFilename)
{
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

    if (pRoot->ult() == nullptr)
        return false;

    m_vecUnits.clear();
    m_vecUnits.reserve(pRoot->ult()->size());

    for (auto itUnit = pRoot->ult()->begin();
        itUnit != pRoot->ult()->end();
        ++itUnit)
    {
        m_vecUnits.push_back(*(*itUnit));
    }

    return true;
}

// generate flatbuffer object to serialise
bool CMitFbMapType1::Write(std::string strFilename)
{
    auto vecFbUnits = m_builder.CreateVectorOfStructs(m_vecUnits);

    // create flatbuffers for Map
    auto mitMap = CreateMapRoot(m_builder
                    , m_eMapType
                    , m_lotInfo
                    , m_waferInfo
                    , 0
                    , vecFbUnits
                    , 0
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

// Type1
void CMitFbMapType1::AddUnit(const MitMapType::stUnitInfo &unit)
{
    m_vecUnits.push_back(unit);
}

void CMitFbMapType1::AddUnits(const std::vector<MitMapType::stUnitInfo> &vecUnits)
{
    m_vecUnits = vecUnits;
}

void CMitFbMapType1::GetUnits(std::vector<MitMapType::stUnitInfo> &vecUnits)
{
    vecUnits = m_vecUnits;
}


