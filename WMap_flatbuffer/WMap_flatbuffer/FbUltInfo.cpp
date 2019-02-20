#include "StdAfx.h"

#include "FbUltInfo.h"

#include <fstream>
#include <iostream>

using namespace ultINFO;

CFbUltInfo::CFbUltInfo(void)
{
}


CFbUltInfo::~CFbUltInfo(void)
{
}

// write to file
bool CFbUltInfo::serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb)
{
     // save to file
    uint8_t *buf = fbb.GetBufferPointer();

    int writesize = fbb.GetSize(); // Returns the size of the buffer that

    // using stream class
    std::ofstream outfile;
    outfile.open(strFilename, std::ios::binary | std::ios::out);

    outfile.write((char*)buf, writesize);
    outfile.close();

    return true;
}

// read from file
bool CFbUltInfo::deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf)
{
    // using stream class
    std::ifstream infile;
    infile.open(strFilename, std::ios::binary | std::ios::in);

    if (!infile.is_open())
    {
        return false;
    }

    infile.seekg(0,std::ios::end);
    std::streamoff size = infile.tellg();
    infile.seekg(0,std::ios::beg);

    fbbBuf.reset(new char [size]);

    infile.read(fbbBuf.get(), size);
    infile.close();

    return true;
}

bool CFbUltInfo::Save(std::string strFilename, std::vector<ultINFO::stUnit> &vecUnits)
{
    flatbuffers::FlatBufferBuilder builder;

    auto vecStruct = builder.CreateVectorOfStructs(vecUnits);

    auto s = CreateUltRoot(builder, vecStruct);
    // complete flatbuffer buidling process
    builder.Finish(s);

    // 5. serialise flatbuffers to file
    serialize(strFilename, builder);
    return true;
}

bool CFbUltInfo::Load(std::string strFilename, std::vector<ultINFO::stUnit> &vecUnits)
{
    std::unique_ptr<char> fbbBuf;

    // 1. deserialise file to buffer
    if (!deserialize(strFilename, fbbBuf))
    {
        return false;
    }

    //
    auto filerecord = GetUltRoot(fbbBuf.get());

    if (filerecord->unit() == nullptr)  // no record
        return false;

    // parse thru the table
    vecUnits.clear();

    for (auto itUnit = filerecord->unit()->begin();
        itUnit != filerecord->unit()->end();
        ++itUnit)
    {
        //vecUnits.push_back(ultINFO::stUnit());
        vecUnits.push_back(ultINFO::stUnit(  itUnit->goodDie(), 
                                    itUnit->placedDie(), 
                                    itUnit->flipper(), 
                                    itUnit->pnp(), 
                                    itUnit->pickForce(), 
                                    itUnit->placeForce(), 
                                    itUnit->purgeForce(), 
                                    itUnit->bincode(), 
                                    itUnit->rejcode(), 
                                    itUnit->unitstate(),
                                    itUnit->inCoor(), 
                                    itUnit->outCoor()));
        //
        //std::cout << "Stn " << nStn << std::endl;
        //std::cout << "Arm " << int(itStn->head()) << "; ";
        //std::cout << "Col " << itStn->col() << "; ";
        //std::cout << "Row " << itStn->row() << "; ";
        //std::cout << "Result " << itStn->result() << "; ";
        //std::cout << "Present " << int(itStn->exist()) << std::endl;

        //std::cout << std::endl;
    }

    return true;
}

//
bool CFbUltInfo::SaveToMem(char *pBaseMem, size_t size, std::vector<ultINFO::stUnit> &vecUnits)
{
    flatbuffers::FlatBufferBuilder builder;

    auto vecStruct = builder.CreateVectorOfStructs(vecUnits);

    auto s = CreateUltRoot(builder, vecStruct);
    // complete flatbuffer buidling process
    builder.Finish(s);

    // 5. serialise flatbuffers to memory
    uint8_t *buf = builder.GetBufferPointer();

    int writesize = builder.GetSize(); // Returns the size of the buffer that

    if (size < writesize)
    {
        // no enough destination size
        return false;
    }

    memcpy((char*)pBaseMem, buf, writesize);
    return true;
}

bool CFbUltInfo::LoadFromMem(char *pBaseMem, size_t size, std::vector<ultINFO::stUnit> &vecUnits)
{
    std::unique_ptr<char> fbbBuf;
    fbbBuf.reset(new char [size]);
    // 1. deserialise memory to buffer
    memcpy(fbbBuf.get(), (char*)pBaseMem, size);

    //
    auto filerecord = GetUltRoot(fbbBuf.get());

    if (filerecord->unit() == nullptr)  // no record
        return false;

    // parse thru the vector of stUnit
    vecUnits.clear();
    for (auto itUnit = filerecord->unit()->begin();
        itUnit != filerecord->unit()->end();
        ++itUnit)
    {
        //vecUnits.push_back(ultINFO::stUnit());
        vecUnits.push_back(ultINFO::stUnit(  itUnit->goodDie(), 
                                    itUnit->placedDie(), 
                                    itUnit->flipper(), 
                                    itUnit->pnp(), 
                                    itUnit->pickForce(), 
                                    itUnit->placeForce(), 
                                    itUnit->purgeForce(), 
                                    itUnit->bincode(), 
                                    itUnit->rejcode(), 
                                    itUnit->unitstate(),
                                    itUnit->inCoor(), 
                                    itUnit->outCoor()));
        //
        //std::cout << "Stn " << nStn << std::endl;
        //std::cout << "Arm " << int(itStn->head()) << "; ";
        //std::cout << "Col " << itStn->col() << "; ";
        //std::cout << "Row " << itStn->row() << "; ";
        //std::cout << "Result " << itStn->result() << "; ";
        //std::cout << "Present " << int(itStn->exist()) << std::endl;

        //std::cout << std::endl;
    }

    return true;
}