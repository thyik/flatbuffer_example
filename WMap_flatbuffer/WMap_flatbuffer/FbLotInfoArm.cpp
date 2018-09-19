#include "StdAfx.h"

#include "FbLotInfoArm.h"

#include <fstream>
#include <iostream>

using namespace lotinfo_arm;

CFbLotInfoArm::CFbLotInfoArm(void)
{
}


CFbLotInfoArm::~CFbLotInfoArm(void)
{
}

// write to file
bool CFbLotInfoArm::serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb)
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
bool CFbLotInfoArm::deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf)
{
    // using stream class
    std::ifstream infile;
    infile.open(strFilename, std::ios::binary | std::ios::in);
    infile.seekg(0,std::ios::end);
    std::streamoff size = infile.tellg();
    infile.seekg(0,std::ios::beg);

    fbbBuf.reset(new char [size]);

    infile.read(fbbBuf.get(), size);
    infile.close();

    return true;
}

bool CFbLotInfoArm::Save(std::string strFilename)
{
    flatbuffers::FlatBufferBuilder builder;

    std::vector<flatbuffers::Offset<lotinfo_arm::ARM_RECORD>> vecArmRecord;
    std::vector<flatbuffers::Offset<ARM>> vecArm;
    long lPass=10;
    long lFail=20;

    auto tablename= builder.CreateString("Demo Tbale");

    // 1. create records
    // Flipper Arm record
    auto name = builder.CreateString("Flipper Pick Arm");
    // 2. create arm data
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));

    auto vecOffsetArm = builder.CreateVector(vecArm);
    
    vecArmRecord.push_back(CreateARM_RECORD(builder, name, vecOffsetArm));

    /// PnP Arm record
    name = builder.CreateString("PnP Pick Arm");
    // create arm data
    vecArm.clear();
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));

    vecOffsetArm = builder.CreateVector(vecArm);
    
    vecArmRecord.push_back(CreateARM_RECORD(builder, name, vecOffsetArm));
    ///

    // 3. create records vector
    auto r = builder.CreateVector(vecArmRecord);
    
    // create root table
    auto s = CreateTABLE_ITEM(builder, tablename, r);
    //
    // 4. complete flatbuffer buidling process
    builder.Finish(s);

    // 5. serialise flatbuffers to file
    serialize(strFilename, builder);
    return true;
}

bool CFbLotInfoArm::Load(std::string strFilename)
{
    std::unique_ptr<char> fbbBuf;

    // 1. deserialise file to buffer
    if (!deserialize(strFilename, fbbBuf))
    {
        return false;
    }

    //
    auto filerecord = GetTABLE_ITEM(fbbBuf.get());

    if (filerecord->lotinfo() == nullptr)  // no record
        return false;

    // parse thru the table
    for (auto itRecord = filerecord->lotinfo()->begin();
        itRecord != filerecord->lotinfo()->end();
        ++itRecord)
    {
        std::cout << std::endl;
        std::cout << '[' << itRecord->name()->str() << ']';
        std::cout << std::endl;

        int nArm=1;
        for (auto it = itRecord->stats()->begin();
            it != itRecord->stats()->end();
            ++it, nArm++)
        {
            //
            std::cout << "Arm " << nArm << std::endl;
            std::cout << "Pass = ";
            std::cout << it->pass();
            std::cout << std::endl;
            std::cout << "Fail = ";
            std::cout << it->fail();
            std::cout << std::endl;

        }
    }

    return true;
}

//
bool CFbLotInfoArm::GetArm(std::string strName, std::vector<lotinfo_arm::ARM> &vecArm)
{

    return true;
}