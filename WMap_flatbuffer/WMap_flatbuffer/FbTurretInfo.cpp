#include "StdAfx.h"

#include "FbTurretInfo.h"

#include <fstream>
#include <iostream>

using namespace turretINFO;

CFbTurretInfo::CFbTurretInfo(void)
{
}


CFbTurretInfo::~CFbTurretInfo(void)
{
}

// write to file
bool CFbTurretInfo::serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb)
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
size_t CFbTurretInfo::deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf)
{
    // using stream class
    std::ifstream infile;
    infile.open(strFilename, std::ios::binary | std::ios::in);
    //
    if (!infile.is_open())
    {
        return 0;
    }

    infile.seekg(0,std::ios::end);
    std::streamoff size = infile.tellg();
    infile.seekg(0,std::ios::beg);

    fbbBuf.reset(new char [size]);

    infile.read(fbbBuf.get(), size);
    infile.close();

    return size;
}

bool CFbTurretInfo::Save(std::string strFilename, std::vector<turretINFO::stStnInfo> &vecStn)
{
    flatbuffers::FlatBufferBuilder builder;

    auto vecStruct = builder.CreateVectorOfStructs(vecStn);

    auto s = CreateINFO(builder, vecStruct);
    // complete flatbuffer buidling process
    builder.Finish(s);

    // 5. serialise flatbuffers to file
    serialize(strFilename, builder);
    return true;
}

bool CFbTurretInfo::Load(std::string strFilename, std::vector<turretINFO::stStnInfo> &vecStn)
{
    std::unique_ptr<char> fbbBuf;

    // 1. deserialise file to buffer
    size_t size = deserialize(strFilename, fbbBuf);
    if (size == 0)
    {
        return false;
    }

    // verify buffer content is valid
    if(!VerifyINFOBuffer(flatbuffers::Verifier((const uint8_t*)fbbBuf.get(), size)))
    {
        // invalid content
        return false;
    }

    //
    auto filerecord = GetINFO(fbbBuf.get());

    if (filerecord->turret() == nullptr)  // no record
        return false;

    // parse thru the table
    vecStn.clear();
    int nStn=1;
    for (auto itStn = filerecord->turret()->begin();
        itStn != filerecord->turret()->end();
        ++itStn, nStn++)
    {
        vecStn.push_back(stStnInfo(itStn->head(), itStn->col(), itStn->row(), itStn->result(), itStn->exist(), stXYT()));
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
bool CFbTurretInfo::SaveToMem(char *pBaseMem, size_t size, std::vector<turretINFO::stStnInfo> &vecStn)
{
    flatbuffers::FlatBufferBuilder builder;

    auto vecStruct = builder.CreateVectorOfStructs(vecStn);

    auto s = CreateINFO(builder, vecStruct);
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

bool CFbTurretInfo::LoadFromMem(char *pBaseMem, size_t size, std::vector<turretINFO::stStnInfo> &vecStn)
{
    std::unique_ptr<char> fbbBuf;
    fbbBuf.reset(new char [size]);
    // 1. deserialise memory to buffer
    memcpy(fbbBuf.get(), (char*)pBaseMem, size);

    // verify buffer content is valid
    if(!VerifyINFOBuffer(flatbuffers::Verifier((const uint8_t*)fbbBuf.get(), size)))
    {
        // invalid content
        return false;
    }
    //
    auto filerecord = GetINFO(fbbBuf.get());
    if (filerecord->turret() == nullptr)  // no record
        return false;

    // parse thru the table
    vecStn.clear();
    int nStn=1;
    for (auto itStn = filerecord->turret()->begin();
        itStn != filerecord->turret()->end();
        ++itStn, nStn++)
    {
        vecStn.push_back(stStnInfo(itStn->head(), itStn->col(), itStn->row(), itStn->result(), itStn->exist(), stXYT()));
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