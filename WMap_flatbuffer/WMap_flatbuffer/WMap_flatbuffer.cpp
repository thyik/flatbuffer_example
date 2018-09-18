// WMap_flatbuffer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\schema\mit_WMap_generated.h"

using namespace MitWMap;
void loadFlatbuffer();

int _tmain(int argc, _TCHAR* argv[])
{
    loadFlatbuffer();
	return 0;
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
