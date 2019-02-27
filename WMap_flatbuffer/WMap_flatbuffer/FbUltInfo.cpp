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
size_t CFbUltInfo::deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf)
{
    // using stream class
    std::ifstream infile;
    infile.open(strFilename, std::ios::binary | std::ios::in);

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


void CFbUltInfo::StartBuild(size_t size)
{
    m_vecOffsetUnits.clear();
    m_vecOffsetUnits.reserve(size);

    m_builder.Clear();
}

void CFbUltInfo::AddUnit(const stUnitDto &unit)
{
    // construct offset vector for fb

    auto name1 = m_builder.CreateString(unit.lotId);
    auto name2 = m_builder.CreateString(unit.inWaferid);
    auto name3 = m_builder.CreateString(unit.outWaferid);
    m_vecOffsetUnits.push_back(CreateIUnit(m_builder, 
                name1,
                unit.goodDie,
                unit.placedDie,
                unit.flipper,
                unit.pnp,
                unit.pickForce,
                unit.placeForce,
                unit.purgeForce,
                unit.bincode,
                unit.rejcode,
                unit.unitstate,
                &ultINFO::stXYTheta(unit.position.fX, unit.position.fY, unit.position.fTheta),  
                name2,
                &ultINFO::stXY(unit.inCoor.shX, unit.inCoor.shY),
                name3,
                &ultINFO::stXY(unit.outCoor.shX, unit.outCoor.shY)));
}


bool CFbUltInfo::Save(std::string strFilename)
{
   // 3. create records vector
    auto r = m_builder.CreateVector(m_vecOffsetUnits);
    //
    //// create root table
    auto s = CreateUltRoot(m_builder, r);
    //

    // complete flatbuffer buidling process
    m_builder.Finish(s);

    // 5. serialise flatbuffers to file
    serialize(strFilename, m_builder);
    return true;
}

bool CFbUltInfo::Save(std::string strFilename, std::vector<stUnitDto> &vecUnits)
{
    flatbuffers::FlatBufferBuilder builder;

    // construct offset vector for fb
    std::vector<flatbuffers::Offset<IUnit>> vecOffsetUnits;

    vecOffsetUnits.reserve(vecUnits.size());

    for (auto it = vecUnits.begin();
        it != vecUnits.end();
        ++it)
    {
        auto name1 = builder.CreateString(it->lotId);
        auto name2 = builder.CreateString(it->inWaferid);
        auto name3 = builder.CreateString(it->outWaferid);
        vecOffsetUnits.push_back(CreateIUnit(builder, 
                    name1,
                    it->goodDie,
                    it->placedDie,
                    it->flipper,
                    it->pnp,
                    it->pickForce,
                    it->placeForce,
                    it->purgeForce,
                    it->bincode,
                    it->rejcode,
                    it->unitstate,
                    &ultINFO::stXYTheta(it->position.fX, it->position.fY, it->position.fTheta),  
                    name2,
                    &ultINFO::stXY(it->inCoor.shX, it->inCoor.shY),
                    name3,
                    &ultINFO::stXY(it->outCoor.shX, it->outCoor.shY)));
    }
    // 3. create records vector
    auto r = builder.CreateVector(vecOffsetUnits);
    
    // create root table
    auto s = CreateUltRoot(builder, r);
    //

    // complete flatbuffer buidling process
    builder.Finish(s);

    // 5. serialise flatbuffers to file
    serialize(strFilename, builder);
    return true;
}

bool CFbUltInfo::Load(std::string strFilename, std::vector<stUnitDto> &vecUnits)
{
    std::unique_ptr<char> fbbBuf;

    // 1. deserialise file to buffer
    size_t size = deserialize(strFilename, fbbBuf);

    if (size == 0)
    {
        return false;
    }

    // verify buffer content is valid
    if(!VerifyUltRootBuffer(flatbuffers::Verifier((const uint8_t*)fbbBuf.get(), size)))
    {
        // invalid content
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
        vecUnits.push_back(stUnitDto(  itUnit->lotId()->str(),
                                    itUnit->goodDie(), 
                                    itUnit->placedDie(), 
                                    itUnit->flipper(), 
                                    itUnit->pnp(), 
                                    itUnit->pickForce(), 
                                    itUnit->placeForce(), 
                                    itUnit->purgeForce(), 
                                    itUnit->bincode(), 
                                    itUnit->rejcode(), 
                                    itUnit->unitstate(),
                                    stXYThetaDto(itUnit->position()->x(), itUnit->position()->y(), itUnit->position()->theta()),
                                    itUnit->inWaferid()->str(),
                                    stXYDto(itUnit->inCoor()->x(), itUnit->inCoor()->y()), 
                                    itUnit->outWaferid()->str(),
                                    stXYDto(itUnit->outCoor()->x(), itUnit->outCoor()->y())));
    }

    return true;
}

//
bool CFbUltInfo::SaveToMem(char *pBaseMem, size_t size, std::vector<stUnitDto> &vecUnits)
{
    flatbuffers::FlatBufferBuilder builder;

   // construct offset vector for fb
    std::vector<flatbuffers::Offset<IUnit>> vecOffsetUnits;

    vecOffsetUnits.reserve(vecUnits.size());

    for (auto it = vecUnits.begin();
        it != vecUnits.end();
        ++it)
    {
        auto name1 = builder.CreateString(it->lotId);
        auto name2 = builder.CreateString(it->inWaferid);
        auto name3 = builder.CreateString(it->outWaferid);
        vecOffsetUnits.push_back(CreateIUnit(builder, 
                    name1,
                    it->goodDie,
                    it->placedDie,
                    it->flipper,
                    it->pnp,
                    it->pickForce,
                    it->placeForce,
                    it->purgeForce,
                    it->bincode,
                    it->rejcode,
                    it->unitstate,
                    &ultINFO::stXYTheta(it->position.fX, it->position.fY, it->position.fTheta),  
                    name2,
                    &ultINFO::stXY(it->inCoor.shX, it->inCoor.shY),
                    name3,
                    &ultINFO::stXY(it->outCoor.shX, it->outCoor.shY)));
    }
    // 3. create records vector
    auto r = builder.CreateVector(vecOffsetUnits);

    auto s = CreateUltRoot(builder, r);
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

bool CFbUltInfo::LoadFromMem(char *pBaseMem, size_t size, std::vector<stUnitDto> &vecUnits)
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
        vecUnits.push_back(stUnitDto(  itUnit->lotId()->str(),
                                    itUnit->goodDie(), 
                                    itUnit->placedDie(), 
                                    itUnit->flipper(), 
                                    itUnit->pnp(), 
                                    itUnit->pickForce(), 
                                    itUnit->placeForce(), 
                                    itUnit->purgeForce(), 
                                    itUnit->bincode(), 
                                    itUnit->rejcode(), 
                                    itUnit->unitstate(),
                                    stXYThetaDto(itUnit->position()->x(), itUnit->position()->y(), itUnit->position()->theta()),
                                    itUnit->inWaferid()->str(),
                                    stXYDto(itUnit->inCoor()->x(), itUnit->inCoor()->y()), 
                                    itUnit->outWaferid()->str(),
                                    stXYDto(itUnit->outCoor()->x(), itUnit->outCoor()->y())));

    }

    return true;
}