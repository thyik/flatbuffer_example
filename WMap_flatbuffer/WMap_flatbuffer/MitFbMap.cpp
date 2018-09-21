#include "StdAfx.h"
#include "MitFbMap.h"

#include "windows.h"

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace MitMAP;

CMitFbMap::CMitFbMap(void)
{
}


CMitFbMap::~CMitFbMap(void)
{
}

// write to file
bool CMitFbMap::serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb)
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
bool CMitFbMap::deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf)
{
    // using stream class
    std::ifstream infile;
    infile.open(strFilename, std::ios::binary | std::ios::in);

    if (!infile.is_open())
    {
        return false;
    }

    // get file size
    infile.seekg(0,std::ios::end);
    std::streamoff size = infile.tellg();
    infile.seekg(0,std::ios::beg);

    // create buffer size
    fbbBuf.reset(new char [size]);

    // load file content into buffer
    infile.read(fbbBuf.get(), size);
    infile.close();

    return true;
}

bool CMitFbMap::LoadFbMap(std::string strFilename, std::vector<short> &vecMap)
{
    // read / deserialize from file
    DWORD dwStart = GetTickCount();
    if (!deserialize(strFilename, m_fbBuf))
    {
        // fail to read file
        return false;
    }

    // populate map info
    populateInfo();

    // get map matrix
    if (!GetFbMapVector(vecMap))
    {
        // fail to get map content
        return false;
    }

    return true;
}

void CMitFbMap::populateInfo()
{
    auto pMap = GetMAP(m_fbBuf.get());

    m_stInfo.maxColRow.shX = pMap->maxCol();
    m_stInfo.maxColRow.shY = pMap->maxRow();
    m_stInfo.strLotNum     = pMap->lotNum()->str();
    m_stInfo.fDiameter     = pMap->diameter();
    //
    m_stInfo.dieGap           = stFPoint(pMap->dieGapX(), pMap->dieGapY());
    m_stInfo.dieSize          = stFPoint(pMap->dieSizeX(), pMap->dieSizeY());
    m_stInfo.fEdgeClearance   = pMap->edgeClearance();
    m_stInfo.shNotch          = pMap->refNotch();
    m_stInfo.shMapId          = pMap->mapId();
    m_stInfo.shBincodeFormat  = pMap->bincodeFormat();
    m_stInfo.shNulBc          = pMap->nullBin();
    m_stInfo.shRefDieDir      = pMap->refChipDir();

    m_stInfo.vecRefDie.clear();
    if (pMap->refDie() != nullptr)
    {
        for (auto it = pMap->refDie()->begin();
            it != pMap->refDie()->end();
            ++it)
        {
            m_stInfo.vecRefDie.push_back(stPoint(it->x(), it->y()));
        }
    }
    //
    if (pMap->startLoc() != nullptr)
    {
        m_stInfo.stStartLoc = stPoint(pMap->startLoc()->x(), pMap->startLoc()->y());
    }
    //
    m_stInfo.strDesignId = pMap->designId()->str();
    m_stInfo.strDevice   = pMap->device()->str();
    m_stInfo.strFabCode  = pMap->fabCode()->str();
    m_stInfo.strIntCode  = pMap->intCode()->str();

    m_stInfo.strLayout   = pMap->layout()->str();
    m_stInfo.shMapType   = m_stInfo.shMapId = pMap->mapId();

    m_stInfo.strScribId  = pMap->scribId()->str();
    m_stInfo.strScribLot = pMap->scribLot()->str();

    if (pMap->targetDie() != nullptr)
    {
        m_stInfo.vecTargetDie.clear();
        //
        for (auto it = pMap->targetDie()->begin();
            it != pMap->targetDie()->end();
            ++it)
        {
            m_stInfo.vecTargetDie.push_back(stPoint(it->x(), it->y()));
        }
    }

    m_stInfo.strWaferNum = pMap->waferNum()->str();
}

bool CMitFbMap::GetFbMapVector(std::vector<short> &vecMap)
{
    if (m_fbBuf == nullptr)
        return false;
    
    DWORD dwStart = GetTickCount();

    std::cout << "deserialize fbm : " << GetTickCount() - dwStart << std::endl;

    dwStart = GetTickCount();

    auto pMap = GetMAP(m_fbBuf.get());
    std::cout << "get fb pointer : " << GetTickCount() - dwStart << std::endl;

    if (pMap->map() == nullptr)  // no map content
        return false;
    // std::copy 100ms for 800 x 800
    // memcpy      0ms for 800 x 800
    dwStart = GetTickCount();
    vecMap.resize(pMap->map()->size());
    std::cout << "resize fb map : " << GetTickCount() - dwStart << std::endl;

    dwStart = GetTickCount();
    //std::copy(m_pMap->map()->begin(), m_pMap->map()->end(), vecMap.begin());
    std::memcpy(vecMap.data(), pMap->map()->data(), pMap->map()->size() * sizeof(short));
    std::cout << "copy fb map : " << GetTickCount() - dwStart << std::endl;

    // slow : 300ms for 800 x 800
    //dwStart = GetTickCount();
    //vecMap.reserve(pMap->map()->size());
    //std::cout << "reserve fb map : " << GetTickCount() - dwStart << std::endl;

    //dwStart = GetTickCount();
    //std::copy(pMap->map()->begin(), pMap->map()->end(), std::back_inserter(vecMap));
    //std::cout << "backinsert fb map : " << GetTickCount() - dwStart << std::endl;

    return true;
}

// generate flatbuffer object to serialise
bool CMitFbMap::WriteFbMap(std::string strFilename, const std::vector<short> &vecMap)
{
    flatbuffers::FlatBufferBuilder builder;

    // building flatbuffer contents

    // 
    auto waferFab = builder.CreateString("TestWaferC++");
    auto wafernum = builder.CreateString(m_stInfo.strWaferNum);

    auto fabCode   = builder.CreateString(m_stInfo.strFabCode);
    auto intCode   = builder.CreateString(m_stInfo.strIntCode);
    auto lotNum    = builder.CreateString(m_stInfo.strLotNum);
    auto device    = builder.CreateString(m_stInfo.strDevice);
    auto layout    = builder.CreateString(m_stInfo.strLayout);
    auto designId  = builder.CreateString(m_stInfo.strDesignId);
    auto scribId   = builder.CreateString(m_stInfo.strScribId);
    auto scribLot  = builder.CreateString(m_stInfo.strScribLot);
    auto binFormat = format_Hex;

    std::vector<stXY> vecRefDie;
    for (auto it = m_stInfo.vecRefDie.begin();
        it != m_stInfo.vecRefDie.end();
        ++it)
    {
        vecRefDie.push_back(stXY(it->shX, it->shY));
    }

    auto fbRefDie = builder.CreateVectorOfStructs(vecRefDie);
    // generate map matrix content
    auto map_info = builder.CreateVector(vecMap);

    const stXY startLoc(0, 0);

    // create flatbuffers for WaferMap
    auto mitMap = CreateMAP(builder
                    , m_stInfo.maxColRow.shX
                    , m_stInfo.maxColRow.shY
                    , map_info
                    , 0 /* target die */
                    , fbRefDie
                    , m_stInfo.shRefDieDir /* ref chip dir */
                    , m_stInfo.shNotch
                    , m_stInfo.shOrientation
                    , m_stInfo.dieSize.fX
                    , m_stInfo.dieSize.fY
                    , m_stInfo.dieGap.fX
                    , m_stInfo.dieGap.fY
                    , m_stInfo.fEdgeClearance
                    , m_stInfo.fDiameter
                    , wafernum
                    , waferFab
                    , fabCode
                    , intCode
                    , lotNum
                    , device
                    , designId
                    , layout
                    , scribId
                    , scribLot
                    , m_stInfo.shMapId
                    , &startLoc
                    , m_stInfo.shNulBc
                    , (format) m_stInfo.shBincodeFormat);

    // Finish building flatbuffer
    builder.Finish(mitMap);  // Serialize the root of the object.

    // save / serialize to file
    if (!serialize(strFilename, builder))
    {
        // fail to write file
        return false;
    }

    return true;
}


bool CMitFbMap::WriteTextMap(std::string strFilename, const std::vector<short> &vecMap)
{
    // !!! add code to output content in text format !!!

    if (m_fbBuf == nullptr)
    {
        // please load buffer
        return false;
    }

    auto pMap = GetMAP(m_fbBuf.get());

    int nRow = pMap->maxRow();
    int nCol = pMap->maxCol();

#define MAX_BIN_CODE 256
    std::vector<int> vecBinCnt(MAX_BIN_CODE);
    //
    std::ofstream outfile(strFilename);

    if (!outfile.is_open())
        return false;

    // headers
    BasicInfoText(outfile);

    // start print matrix
    outfile << "WAFER_DATA:" << std::endl;
    outfile << "----------" << std::endl;

    int i = 0, j = 0;
    int nCount=0;
    short shBin = 0;
    int nLastColIndex = nCol - 1;
    for (; i < nRow; i++)
    {
        // setup formating
        outfile << std::uppercase << std::hex << std::right ;
        //
        for (j = 0; j < nCol; j++, nCount++)
        {

            if (!vecMap.empty())
            {
                shBin = vecMap[nCount];
            }

            // slightly fast to setup formatting once only per row
            //outfile << std::uppercase << std::hex << std::right << std::setfill('0') << std::setw(2) << shBin;
            outfile << std::setw(2) << std::setfill('0') << shBin;

            if (j != nLastColIndex)
            {
                outfile << ' ';
            }

            // bin count
            vecBinCnt[shBin]++;
        }

        // set row legend
        outfile << "| " << std::setfill('0') << std::setw(2) << std::dec << i << std::endl;

    }
    
    // print col legend
    for (j = 0; j < nCol; j++) // start from 0 col
    {
        if (j == 0)
        {
            outfile << "0--";
        }
        else if (j == 5)
        {
            outfile << "5--";
        }
        else if ((j % 10) == 0)
        {
            outfile << "+++";
        }
        else
        {
            outfile << "---";
        }
    }

    outfile << std::endl;
    outfile << std::endl;

    // print bin counter
    int nBinCode;
    for (nBinCode = 0; nBinCode < MAX_BIN_CODE; nBinCode++)
    {
        outfile << "BIN ";
        outfile << std::setfill('0') << std::setw(2) << std::dec << nBinCode;
        outfile << ' (' << std::setfill('0') << std::setw(2) << std::hex << nBinCode << ')';
        outfile << " = " << std::dec << vecBinCnt[nBinCode] << std::endl;
    }

    outfile.close();

    return true;
}


bool CMitFbMap::BasicInfoText(std::ofstream &outfile)
{
    auto pMap = GetMAP(m_fbBuf.get());

    outfile << "WAFER_FAB    = " << ((pMap->waferFab() == nullptr) ? "" : pMap->waferFab()->str()) << std::endl;
    outfile << "FAB_CODE     = " << ((pMap->fabCode() == nullptr) ? "" : pMap->fabCode()->str()) << std::endl;
    outfile << "INT_CODE     = " << ((pMap->intCode() == nullptr) ? "" : pMap->intCode()->str()) << std::endl;
    outfile << "LOT_NUM      = " << ((pMap->lotNum() == nullptr) ? "" : pMap->lotNum()->str()) << std::endl;
    outfile << "DEVICE       = " << ((pMap->device() == nullptr) ? "" : pMap->device()->str()) << std::endl;
    outfile << "DESIGN_ID    = " << ((pMap->designId() == nullptr) ? "" : pMap->designId()->str()) << std::endl;
    outfile << "LAYOUT       = " << ((pMap->layout() == nullptr) ? "" : pMap->layout()->str()) << std::endl;
    outfile << "SCRIB_ID     = " << ((pMap->scribId() == nullptr) ? "" : pMap->scribId()->str()) << std::endl;
    outfile << "SCRIB_LOT    = " << ((pMap->scribLot() == nullptr) ? "" : pMap->scribLot()->str()) << std::endl;
    outfile << "WAFER_NUM    = " << ((pMap->waferNum() == nullptr) ? "" : pMap->waferNum()->str()) << std::endl;
    outfile << "MAP_IDTYPE   = " << pMap->mapId() << std::endl;

    //
    int nNumRef = 0;
    if (pMap->refDie() != nullptr)
    {
        nNumRef = pMap->refDie()->size();
    }
    //
    outfile << "REFCHIP_NO   = " << nNumRef << std::endl;
    //
    outfile << "BINCODE_FORMAT = " << pMap->bincodeFormat() << std::endl;
    outfile << "REFCHIP_XYLOC= ";
    
    if (pMap->refDie() != nullptr)
    {
        int nRef=0;
        for (auto it = pMap->refDie()->begin();
            it != pMap->refDie()->end();
            ++it, nRef++)
        {
            outfile << it->x() << ','<< it->y();

            if (nRef != nNumRef - 1)
            {
                outfile << ';';
            }
        }

    }
    else
    {
        outfile << "0,0";
    }

    outfile << std::endl;

    outfile << "REFCHIP_DIR  = " << pMap->refChipDir() << std::endl;
    outfile << "ROT_ANGLE    = " << pMap->degRotated() << std::endl;   // Display actual rotation
    outfile << "MAX ROW/COL  = " << pMap->maxRow() << ',' << pMap->maxCol() << std::endl;
    outfile << "START_XYLOC  = " << ((pMap->startLoc() == nullptr) ? 0 : pMap->startLoc()->x()) << ',' << ((pMap->startLoc() == nullptr) ? 0 : pMap->startLoc()->y()) << std::endl;
    outfile << "X_SIZE       = " << pMap->dieSizeX() << std::endl;
    outfile << "Y_SIZE       = " << pMap->dieSizeY() << std::endl;
    outfile << "Bin Configuration File:" << std::endl;
    outfile << "----------------------" << std::endl;
    outfile << "           MtrBin  LtrBin  ProbeBin" << std::endl;
    outfile << "Mtr_cfg =    1       .       ." << std::endl;
    outfile << "Mtr_cfg =    8       S       A B C D E F G H I J K L" << std::endl;
    outfile << "Mtr_cfg =    5       R      -1 -2" << std::endl;
    outfile << std::endl;

    //CString csMapLocation =  CIniFile::GetString(RUNTIME_INI, RECIPE_INFO_SECTION_NAME,
    //                                             "Map Location", "Prompt Map", FALSE);

    //if (csMapLocation == "Oracle")
    //{
    //    outfile << "PROBER_FILE = %s\n", m_csProberFile);
    //    outfile << "ID = %d\n", m_iID);
    //    outfile << "PASS = %d\n", m_iPass);
    //    outfile << "FAIL = %d\n", m_iFail);
    //    outfile << "SOURCE = %s\n", m_csSource);
    //    outfile << "MAP_VER = %d\n", m_iVer);
    //}
    //else
    {
        //outfile << "XREF = " << pMap->refDie());
        //outfile << "YREF = %d\n", m_iYRef);
    }

    //outfile << "BINCODE_EQU = " << pMap->bincodeEq()->str() << std::endl;
    outfile << "NULLBINCODE = " << (char) pMap->nullBin() << std::endl;

    //std::ostringstream os("");

    //if (!m_vecPickBinCode.empty())
    //{
    //    for (auto it = m_vecPickBinCode.begin(); it != m_vecPickBinCode.end(); ++it)
    //    {
    //        if (os.str().empty())
    //        {
    //            os << *it;
    //        }
    //        else
    //        {
    //            os << "," << *it;
    //        }
    //    }
    //}

    //outfile << "PICK BINCODE = %s\n" << std::endl;
    outfile << std::endl;

    return true;
}
