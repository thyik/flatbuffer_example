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

    auto waferid = builder.CreateString("TestWaferC++");
    auto wafernum = 1;
    auto lotid = builder.CreateString("LotWaferC++");
    auto binFormat = format_Hex;
    //
    short map_data[] = { 0, 11, 2, 3, 4, 5, 6, 77, 8, 9 };
    auto map_info = builder.CreateVector(map_data, 10);

    auto mitMap = CreateWaferMap(builder, waferid, wafernum, lotid, binFormat, map_info);

    builder.Finish(mitMap);  // Serialize the root of the object.

  //auto weapon_one_name = builder.CreateString("Sword");
  //short weapon_one_damage = 3;

    auto readMap = GetWaferMap(builder.GetBufferPointer());

    printf("Waferid : %s\n", readMap->waferid()->str().c_str());
    printf("WaferNum : %d\n", readMap->wafernum());
    printf("Format : %d\n", readMap->binFormat());
    printf("Lotid : %s\n", readMap->lotid()->str().c_str());

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
    printf("Waferid : %s\n",    filemap->waferid()->str().c_str());
    printf("WaferNum : %d\n",   filemap->wafernum());
    printf("Format : %d\n",     filemap->binFormat());
    printf("Lotid : %s\n",      filemap->lotid()->str().c_str());

    for (auto it = filemap->map()->begin();
        it != filemap->map()->end();
        ++it)
    {
        printf("%d,", *it);
    }
}
