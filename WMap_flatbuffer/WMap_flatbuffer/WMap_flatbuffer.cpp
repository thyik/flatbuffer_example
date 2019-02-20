// WMap_flatbuffer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\schema\mit_WMap_generated.h"
#include "FbIni.h"
#include "FbLotInfoArm.h"
#include "MitFbMap.h"
#include "MsgDecode.h"

#include <atlstr.h>  
// for GetTickCount()
#include "Windows.h"
#include "RotateBenchmark.h"
#include "FbTurretInfo.h"
#include "FbUltInfo.h"

#include <iostream>
#include <sstream>

using namespace MitWMap;
void loadFlatbuffer();
void LogError(const char* formatString, ...);
void test2()
{
    int n = std::stoi(" ");
}

void testexception()
{
    test2();
}



int _tmain(int argc, _TCHAR* argv[])
{

    CRotateBenchmark benchmark;
    benchmark.Rotate90();

    //
    std::string strTmp;
    size_t sizeStr = sizeof(strTmp);

    CString csTestTmp;

    unsigned short nValue=1;
    std::string strTmp1 = "  65535";
    std::istringstream iss(strTmp1);
    iss >> nValue;

    sizeStr = sizeof(csTestTmp);

    csTestTmp = "1234566789";
    sizeStr = sizeof(csTestTmp);

    //int nA = std::stoi(strTmp);

    std::vector<std::string> vecStrings;
    std::vector<std::string> vecStringsTwo;

    vecStrings.reserve(15);

    vecStringsTwo.resize(15);

    for (auto it = vecStringsTwo.begin();
        it != vecStringsTwo.end();
        ++it)
    {
        *it = "1";
    }

    vecStrings = vecStringsTwo;

    vecStrings[0] = "123456789123456789123456789123456789123456789123456789";
    sizeStr = sizeof(vecStrings[0]);

    //
    vecStrings[0].shrink_to_fit();
    sizeStr = sizeof(vecStrings[0]);
    ///
    MC_MSG_GRP mcTemp;

    UINT inData = 9239193392923922;

    int nSize = sizeof(UINT);

    CMsgDecode decode;
    std::string strPacket;
    mcTemp.msgType = 1;
    strcpy(mcTemp.byteMsg, "Test 123456789");
    mcTemp.msgSize = strlen(mcTemp.byteMsg);

    size_t size = 2*sizeof(int) + mcTemp.msgSize;
    strPacket.append((char*)&mcTemp, size);
    decode.appendPacket(strPacket);

    mcTemp.msgType = 0;
    strcpy(mcTemp.byteMsg, "Test 4567");
    mcTemp.msgSize = strlen(mcTemp.byteMsg);
    size = 2*sizeof(int) + mcTemp.msgSize;
    strPacket.clear();
    strPacket.append((char*)&mcTemp, size);
    decode.appendPacket(strPacket);

    MC_DATA msg;
    decode.getMsg(msg);

    decode.getMsg(msg);

    //loadFlatbuffer();
    CMitFbMap fbMitMap;
    int nTotal = 800*800;
    stMapInfo stInfo;

    stInfo.maxColRow.shX = 800;
    stInfo.maxColRow.shY = 800;

    std::vector<short> vecMap(nTotal);

    DWORD dwStart = GetTickCount();

    for (int ni=0; ni<nTotal; ni++)
    {
        vecMap[ni] = (ni % 12);
    }
    //
    std::cout << "generate map : " << GetTickCount() - dwStart << std::endl;
    //
    fbMitMap.SetInfo(stInfo);
    //
    dwStart = GetTickCount();
    fbMitMap.WriteFbMap("D:\\Temp\\FbMap.fbm", vecMap);
    std::cout << "write fbm : " << GetTickCount() - dwStart << std::endl;
    
    std::vector<short> vecLoadMap;

    dwStart = GetTickCount();
    fbMitMap.LoadFbMap("D:\\Temp\\FbMap.fbm", vecLoadMap);
    std::cout << "read fbm : " << GetTickCount() - dwStart << std::endl;

    dwStart = GetTickCount();
    fbMitMap.WriteTextMap("D:\\Temp\\FbMap.map", vecLoadMap);
    std::cout << "write fbm text : " << GetTickCount() - dwStart << std::endl;
    //CFbIni fbIni;

    //fbIni.Save("D:\\Temp\\fbini.bin");
    //fbIni.Load("D:\\Temp\\fbini.bin");

    //CFbLotInfoArm fbLotInfoArm;
    //fbLotInfoArm.Save("D:\\Temp\\fblotinfo_arm.fbb");
    //fbLotInfoArm.Load("D:\\Temp\\fblotinfo_arm.fbb");

    LogError("Test Logger : %s", "Hello123\nHello2\nHello\n");
    int data;


    CFbTurretInfo fbTurret;
    std::vector<turretINFO::stStnInfo> vecStn;
    std::vector<turretINFO::stStnInfo> vecLoadStn;

    vecStn.push_back(turretINFO::stStnInfo(1,2,3,4,0,turretINFO::stXYT()));
    vecStn.push_back(turretINFO::stStnInfo(21,22,23,24,20,turretINFO::stXYT()));

    fbTurret.Save("D:\\Temp\\PnP.fbi", vecStn);
    fbTurret.Load("D:\\Temp\\PnP.fbi", vecLoadStn);

    char szMem[100];
    
    fbTurret.SaveToMem(szMem, 100, vecStn);
    fbTurret.LoadFromMem(szMem, 100, vecLoadStn);

    //
    for (int i=0; i<2; i++)
    {
        try {
            testexception();
        }
        catch (std::exception& e)//(...)
        {
            std::cout << e.what() << '\n';
        }
    }
    std::cout << "end";
    std::cin >> data;


    //// ultINFO
    CFbUltInfo fbUlt;
    std::vector<ultINFO::stUnit> vecUnits;
    vecUnits.reserve(400);
    vecUnits.push_back(ultINFO::stUnit(1,0,0,0,0,0,0,0,0,0,ultINFO::stXY(), ultINFO::stXY()));
    vecUnits.push_back(ultINFO::stUnit(2,0,0,0,0,0,0,0,0,0,ultINFO::stXY(), ultINFO::stXY()));
    vecUnits.push_back(ultINFO::stUnit(3,0,0,0,0,0,0,0,0,0,ultINFO::stXY(), ultINFO::stXY()));

    fbUlt.Save("D:\\Temp\\TnR1.fbu", vecUnits);

    std::vector<ultINFO::stUnit> vecLoadUnits;
    fbUlt.Load("D:\\Temp\\TnR1.fbu", vecLoadUnits);
    //
    for (auto itUnit = vecLoadUnits.begin();
        itUnit != vecLoadUnits.end();
        ++itUnit)
    {
        std::cout << itUnit->goodDie() << std::endl;
    }
    ////
	return 0;
}


void LogError(const char* formatString, ...)
{
    va_list argList;
    va_start(argList, formatString);
    CString cMsg;
    cMsg.FormatV(formatString, argList);
    va_end(argList);

    std::cout << cMsg.GetBuffer();

}

void loadFlatbuffer()
{
    flatbuffers::FlatBufferBuilder builder;

    auto waferFab = builder.CreateString("TestWaferC++");
    auto wafernum = builder.CreateString("1");
    auto lotid = builder.CreateString("LotWaferC++");

    auto fabCode   = builder.CreateString("fabCode C++");
    auto intCode   = builder.CreateString("intCode C++");
    auto lotNum    = builder.CreateString("LotNum C++");
    auto device    = builder.CreateString("device C++");
    auto designId  = builder.CreateString("designId C++");
    auto scribId   = builder.CreateString("scribId C++");
    auto scribLot  = builder.CreateString("scribLot C++");
    auto binFormat = format_Hex;
    //
    short map_data[] = { 0, 11, 2, 3, 4, 5, 6, 77, 8, 9 };
    auto map_info = builder.CreateVector(map_data, 10);

    auto mitMap = CreateWaferMap(builder
                    , 5
                    , 2
                    , map_info
                    , waferFab
                    , fabCode
                    , intCode
                    , lotNum
                    , device
                    , designId
                    , scribId
                    , scribLot
                    , wafernum);

    
    builder.Finish(mitMap);  // Serialize the root of the object.

    
  //auto weapon_one_name = builder.CreateString("Sword");
  //short weapon_one_damage = 3;

    auto readMap = GetWaferMap(builder.GetBufferPointer());

    printf("Waferid : %s\n", readMap->waferFab()->str().c_str());
    printf("WaferNum : %s\n", readMap->waferNum()->str().c_str());
    printf("Lotid : %s\n", readMap->lotNum()->str().c_str());

    for (auto it = readMap->map()->begin();
        it != readMap->map()->end();
        ++it)
    {
        printf("%d,", *it);
    }

    // save to file
    uint8_t *buf = builder.GetBufferPointer();
    int size = builder.GetSize(); // Returns the size of the buffer that
    std::string strfilename = "D:\\Temp\\output.dat";

    FILE *fp;
    fopen_s(&fp, strfilename.c_str(), "wb");

    fwrite(buf, size, 1, fp);
    fclose(fp);


    // read
    std::unique_ptr<uint8_t> buf2;
    buf2.reset(new uint8_t [size]);
    fopen_s(&fp, strfilename.c_str(), "rb");
    fread(buf2.get(), size, 1, fp);
    fclose(fp);

    auto filemap = GetWaferMap(buf2.get());

    printf("\n");
    printf("Waferid : %s\n",    filemap->waferFab()->str().c_str());
    printf("WaferNum : %d\n",   filemap->waferNum()->str().c_str());
    printf("Lotid : %s\n",      filemap->lotNum()->str().c_str());

    for (auto it = filemap->map()->begin();
        it != filemap->map()->end();
        ++it)
    {
        printf("%d,", *it);
    }
}
