#include "StdAfx.h"
#include "MitFbUltMap1.h"

#include "windows.h"

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace MitMapType;

CMitFbUltMap1::CMitFbUltMap1(void)
{
}


CMitFbUltMap1::~CMitFbUltMap1(void)
{
    
}

// write to file
bool CMitFbUltMap1::serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb)
{
    // using stream class
    std::ofstream outfile;
    outfile.open(strFilename, std::ios::binary | std::ios::out);

    if (!outfile.is_open())
    {
        // fail to open fail
        return false;
    }

    // save to file
    uint8_t *buf = fbb.GetBufferPointer();

    int writesize = fbb.GetSize(); // Returns the size of the buffer that
    //
    outfile.write((char*)buf, writesize);
    outfile.close();

    return true;
}

// read from file
size_t CMitFbUltMap1::deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf)
{
    // using stream class
    std::ifstream infile;
    infile.open(strFilename, std::ios::binary | std::ios::in);

    if (!infile.is_open())
    {
        return 0;
    }

    // get file size
    infile.seekg(0,std::ios::end);
    std::streamoff size = infile.tellg();
    infile.seekg(0,std::ios::beg);

    // create buffer size
    fbbBuf.reset(new char [(unsigned int)size]);

    // load file content into buffer
    infile.read(fbbBuf.get(), size);
    infile.close();

    return size;
}

bool CMitFbUltMap1::Read(std::string strFilename)
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

void CMitFbUltMap1::populateInfo()
{
    auto pMap = GetMapRoot(m_fbBuf.get());

    if (pMap->lotInfo() == nullptr)
    {
        return;
    }

    // lotinfo
    m_stLotData.strMachineId    = pMap->lotInfo()->machine() ? pMap->lotInfo()->machine()->str() : "";
    m_stLotData.strLotNum       = pMap->lotInfo()->lotNum()->str();
    m_stLotData.strPackageName  = pMap->lotInfo()->packageName()->str();
    m_stLotData.strRecipeName   = pMap->lotInfo()->recipeName()->str();
    m_stLotData.strShift        = pMap->lotInfo()->shift()->str();
    m_stLotData.strOperator     = pMap->lotInfo()->operator_()->str();

    // wafer info
    m_stWaferData.dieSize       = *pMap->waferInfo()->dieSize();
    m_stWaferData.shNotch       = pMap->waferInfo()->notch();
    m_stWaferData.strWaferId    = pMap->waferInfo()->waferId()->str();
    m_stWaferData.fWaferSize    = pMap->waferInfo()->wafersize();
    m_stWaferData.maxRowCol     = *pMap->waferInfo()->maxRowCol();
    m_stWaferData.dieGap        = *pMap->waferInfo()->dieGap();
    //
    m_stWaferData.targetDie.clear();
    
    if (pMap->waferInfo()->targetDie() != nullptr)
    {
        for (auto it = pMap->waferInfo()->targetDie()->begin();
            it != pMap->waferInfo()->targetDie()->end();
            ++it)
        {
            m_stWaferData.targetDie.push_back(stXY(it->x(), it->y()));
        }
    }
}

void CMitFbUltMap1::StartBuild(size_t size)
{
    m_builder.Clear();

    m_vecUnits.clear();
    m_vecUnits.reserve(size);

    //
    //m_lotInfo = 0;
    //m_waferInfo = 0;

}

void CMitFbUltMap1::AddLotInfo()
{
    m_lotInfo = CreateTblLotInfo(m_builder, 
                                    m_builder.CreateString(m_stLotData.strMachineId), 
                                    m_builder.CreateString(m_stLotData.strLotNum), 
                                    m_builder.CreateString(m_stLotData.strPackageName), 
                                    m_builder.CreateString(m_stLotData.strRecipeName), 
                                    m_builder.CreateString(m_stLotData.strShift), 
                                    m_builder.CreateString(m_stLotData.strOperator));
    
}

void CMitFbUltMap1::AddWaferInfo()
{
    m_waferInfo = CreateTblWaferInfo(m_builder, 
                                        &m_stWaferData.dieSize, 
                                        m_stWaferData.shNotch, 
                                        m_builder.CreateVectorOfStructs(m_stWaferData.targetDie),
                                        m_builder.CreateString(m_stWaferData.strWaferId), 
                                        m_stWaferData.fWaferSize, 
                                        &m_stWaferData.maxRowCol, 
                                        &m_stWaferData.dieGap);
    
}

void CMitFbUltMap1::AddUnit(const MitMapType::stUnitInfo &unit)
{
    m_vecUnits.push_back(unit);
}

void CMitFbUltMap1::AddUnits(const std::vector<MitMapType::stUnitInfo> &vecUnits)
{
    m_vecUnits = vecUnits;
}

// generate flatbuffer object to serialise
bool CMitFbUltMap1::Write(std::string strFilename)
{
    auto vecFbUnits = m_builder.CreateVectorOfStructs(m_vecUnits);

    // create flatbuffers for Map
    auto mitMap = CreateMapRoot(m_builder
                    , MapType_MAP_ULT_C330
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

stLotInfo& CMitFbUltMap1::LotData()
{
    return m_stLotData;
}

stWaferInfo& CMitFbUltMap1::WaferData()
{
    return m_stWaferData;
}

void CMitFbUltMap1::GetUnits(std::vector<MitMapType::stUnitInfo> &vecUnits)
{
    vecUnits = m_vecUnits;
}
