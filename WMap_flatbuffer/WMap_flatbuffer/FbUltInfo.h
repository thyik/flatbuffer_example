#pragma once

#include "..\..\schema\ultINFO_generated.h"

#include <string>

// dto : data transfer object struct
typedef struct _stXYThetaDto {
    float fX;
    float fY;
    float fTheta;

    _stXYThetaDto(float x = 0.0, float y = 0.0, float theta = 0.0)
        : fX(x)
        , fY(y)
        , fTheta(theta)
    {
    };
} stXYThetaDto;

typedef struct _stXYDto {
    short shX;
    short shY;

    _stXYDto(short x = 0, short y = 0)
        : shX(x)
        , shY(y)
    {
    };
} stXYDto;

typedef struct _stUnitDto {
    std::string     lotId;
    int             goodDie;
    int             placedDie;
    short           flipper;
    short           pnp;
    short           pickForce;
    short           placeForce;
    short           purgeForce;
    short           bincode;
    short           rejcode;
    unsigned long   unitstate;
    stXYThetaDto    position;
    std::string     inWaferid;
    stXYDto         inCoor;
    std::string     outWaferid;
    stXYDto         outCoor;

    _stUnitDto(const std::string &_lotid, 
                int _goodDie, int _placedDie, 
                short _flipper, short _pnp, 
                short _pickForce, short _placeForce, short _purgeForce, 
                short _bincode, short _rejcode, 
                unsigned long _unitstate,
                stXYThetaDto      &_position,
                const std::string &_inWaferid,
                const stXYDto     &_inCoor,
                const std::string &_outWaferid,
                const stXYDto     &_outCoor)
        : lotId     (_lotid)
        , goodDie   (_goodDie)
        , placedDie (_placedDie)
        , flipper   (_flipper)
        , pnp       (_pnp)
        , pickForce (_pickForce)
        , placeForce(_placeForce)
        , purgeForce(_purgeForce)
        , bincode   (_bincode)
        , rejcode   (_rejcode)
        , unitstate (_unitstate)
        , position  (_position)
        , inWaferid (_inWaferid)
        , inCoor    (_inCoor)
        , outWaferid(_outWaferid)
        , outCoor(_outCoor)
    {
    };

} stUnitDto;

class CFbUltInfo
{
public:
    CFbUltInfo(void);
    ~CFbUltInfo(void);

    bool Load(std::string strFilename, std::vector<stUnitDto> &vecUnits);
    bool Save(std::string strFilename, std::vector<stUnitDto> &vecUnits);

    bool SaveToMem(char *pBaseMem, size_t size, std::vector<stUnitDto> &vecUnits);
    bool LoadFromMem(char *pBaseMem, size_t size, std::vector<stUnitDto> &vecUnits);

    void StartBuild(size_t size);
    void AddUnit(const stUnitDto &unit);
    bool Save(std::string strFilename);

private:
    bool serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb);
    size_t deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf);

    flatbuffers::FlatBufferBuilder m_builder;

    // construct offset vector for fb
    std::vector<flatbuffers::Offset<ultINFO::IUnit>> m_vecOffsetUnits;

};

