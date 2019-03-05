#include "StdAfx.h"
#include "IMitFbMapType.h"

#include "windows.h"

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace MitMapType;

CIMitFbMapType::CIMitFbMapType(void)
{
}


CIMitFbMapType::~CIMitFbMapType(void)
{
    
}

// write to file
bool CIMitFbMapType::serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb)
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
size_t CIMitFbMapType::deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf)
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


void CIMitFbMapType::AddLotInfo()
{
    m_lotInfo = CreateTblLotInfo(m_builder, 
                                    m_builder.CreateString(LotData().strMachineId), 
                                    m_builder.CreateString(LotData().strLotNum), 
                                    m_builder.CreateString(LotData().strPackageName), 
                                    m_builder.CreateString(LotData().strRecipeName), 
                                    m_builder.CreateString(LotData().strShift), 
                                    m_builder.CreateString(LotData().strOperator));
    
}

void CIMitFbMapType::AddWaferInfo()
{

    m_waferInfo = CreateTblWaferInfo(m_builder, 
                                        &WaferData().dieSize, 
                                        WaferData().shNotch, 
                                        m_builder.CreateVectorOfStructs(WaferData().targetDie),
                                        m_builder.CreateString(WaferData().strWaferId), 
                                        WaferData().fWaferSize, 
                                        &WaferData().maxRowCol, 
                                        &WaferData().dieGap,
                                        WaferData().edgeClearance,
                                        WaferData().pickDegree);
    
}

void CIMitFbMapType::populateInfo()
{
    auto pMap = GetMapRoot(m_fbBuf.get());

    if (pMap->lotInfo() == nullptr)
    {
        return;
    }

    // lotinfo
    m_stLotData.strMachineId    = pMap->lotInfo()->machine() ? pMap->lotInfo()->machine()->str() : "";
    m_stLotData.strLotNum       = pMap->lotInfo()->lotNum() ? pMap->lotInfo()->lotNum()->str() : "";
    m_stLotData.strPackageName  = pMap->lotInfo()->packageName() ? pMap->lotInfo()->packageName()->str() : "";
    m_stLotData.strRecipeName   = pMap->lotInfo()->recipeName() ? pMap->lotInfo()->recipeName()->str() : "";
    m_stLotData.strShift        = pMap->lotInfo()->shift() ? pMap->lotInfo()->shift()->str() : "";
    m_stLotData.strOperator     = pMap->lotInfo()->operator_() ? pMap->lotInfo()->operator_()->str() : "";

    if (pMap->waferInfo() == nullptr)
    {
        return;
    }
    // wafer info
    m_stWaferData.dieSize       = pMap->waferInfo()->dieSize() ? *pMap->waferInfo()->dieSize() : stfXY();
    m_stWaferData.shNotch       = pMap->waferInfo()->notch();
    m_stWaferData.strWaferId    = pMap->waferInfo()->waferId() ? pMap->waferInfo()->waferId()->str() : "";
    m_stWaferData.fWaferSize    = pMap->waferInfo()->wafersize();
    m_stWaferData.maxRowCol     = pMap->waferInfo()->maxRowCol() ? *pMap->waferInfo()->maxRowCol() : stXY();
    m_stWaferData.dieGap        = pMap->waferInfo()->dieGap() ? *pMap->waferInfo()->dieGap() : stfXY();
    //
    m_stWaferData.edgeClearance = pMap->waferInfo()->edgeClearance();
    m_stWaferData.pickDegree    = pMap->waferInfo()->pickDegree();
    //
    m_stWaferData.targetDie.clear();
    
    if (pMap->waferInfo()->targetDie())
    {
        for (auto it = pMap->waferInfo()->targetDie()->begin();
            it != pMap->waferInfo()->targetDie()->end();
            ++it)
        {
            m_stWaferData.targetDie.push_back(stXY(it->x(), it->y()));
        }
    }
}

void CIMitFbMapType::StartBuild(size_t size)
{
    m_builder.Clear();

    m_vecUnits.clear();

    m_vecType2TblUnitInfo.clear();
    m_vecType2Units.clear();
    //m_vecType2UnitInfo.clear();  // this is for read use
    m_vecFbUnits = 0;

    switch (m_eMapType)
    {
        case MapType_MAP_GENERIC:
        {
            break;
        }

        case MapType_MAP_ULT_C330:
        {
            m_vecUnits.reserve(size);
            break;
        }

        case MapType_MAP_ULT_MR3:
        {
            m_vecType2TblUnitInfo.reserve(size);
            m_vecType2Units.reserve(size);
        }
    }

    //
    //m_lotInfo = 0;
    //m_waferInfo = 0;

}

stFbLotInfo& CIMitFbMapType::LotData()
{
    return m_stLotData;
}

stFbWaferInfo& CIMitFbMapType::WaferData()
{
    return m_stWaferData;
}

