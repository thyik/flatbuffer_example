#include "StdAfx.h"
#include "FbLotInfoArm.h"

#include "..\..\schema\lotinfo_arm_generated.h"

#include <fstream>
#include <iostream>

using namespace lotinfo_arm;

CFbLotInfoArm::CFbLotInfoArm(void)
{
}


CFbLotInfoArm::~CFbLotInfoArm(void)
{
}

bool CFbLotInfoArm::Load(std::string strFilename)
{

    std::unique_ptr<char> buf2;
    // using stream class
    std::ifstream infile;
    infile.open(strFilename, std::ios::binary | std::ios::in);
    infile.seekg(0,std::ios::end);
    size_t size = infile.tellg();
    infile.seekg(0,std::ios::beg);

    buf2.reset(new char [size]);

    infile.read(buf2.get(), size);
    infile.close();

    auto filerecord = GetARM_RECORD(buf2.get());

    if (filerecord->stats() == nullptr)
        return false;

    std::cout << std::endl;
    std::cout << '[' << filerecord->fieldname()->str() << ']';
    std::cout << std::endl;

    int nArm=1;
    for (auto it = filerecord->stats()->begin();
        it != filerecord->stats()->end();
        ++it, nArm++)
    {
        std::cout << "Arm " << nArm << std::endl;
        std::cout << "Pass = ";
        std::cout << it->pass();
        std::cout << std::endl;
        std::cout << "Fail = ";
        std::cout << it->fail();
        std::cout << std::endl;

    }

    return true;
}

bool CFbLotInfoArm::Save(std::string strFilename)
{
    flatbuffers::FlatBufferBuilder builder;

    std::vector<flatbuffers::Offset<ARM>> vecArm;
    long lPass=0;
    long lFail=0;
    auto name = builder.CreateString("Flipper Pick Arm");
    // create arm table
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));
    vecArm.push_back(CreateARM(builder, lPass++, lFail++));

    auto vecOffsetArm = builder.CreateVector(vecArm);

    // create root table
    auto armRecord = CreateARM_RECORD(builder, name, vecOffsetArm);

    builder.Finish(armRecord);
    
    armRecord = CreateARM_RECORD(builder, name, vecOffsetArm);

     // save to file
    uint8_t *buf = builder.GetBufferPointer();

    int writesize = builder.GetSize(); // Returns the size of the buffer that

    // using stream class
    std::ofstream outfile;
    outfile.open(strFilename, std::ios::binary | std::ios::out);

    outfile.write((char*)buf, writesize);
    outfile.close();

    return true;
}