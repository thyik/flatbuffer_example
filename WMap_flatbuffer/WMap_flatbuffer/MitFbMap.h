#pragma once

#include <string>

//#include "..\flatbuffers\schema\mitMAP_generated.h"
#include "..\..\schema\mitMAP_generated.h"

typedef struct _stFPoint {
    float fX;
    float fY;

    // ctor
    _stFPoint(float x = 0.0, float y = 0.0)
        : fX (x)
        , fY (y)
    {
    };
} stFPoint;

typedef struct _stPoint {
    short shX;
    short shY;
    // ctor
    _stPoint(short x = 0.0, short y = 0.0)
        : shX (x)
        , shY (y)
    {
    };
} stPoint;

typedef struct _stMapInfo {
    std::string strFabCode;
    std::string strIntCode;
    std::string strLotNum;
    std::string strDevice;
    std::string strDesignId;
    std::string strLayout;
    std::string strScribId;
    std::string strScribLot;
    std::string strWaferNum;
    short       shMapId;
    short       shBincodeFormat;

    stPoint     maxColRow;
    stFPoint    dieSize;
    stFPoint    dieGap;
    float       fEdgeClearance;
    float       fDiameter;
    short       shOrientation;
    short       shNotch;
    short       shNulBc;

    std::vector<stPoint>   vecRefDie;
    short       shRefDieDir;
    short       shMapType;

    std::vector<stPoint>   vecTargetDie;

    stPoint     stStartLoc;

    _stMapInfo() 
        : strFabCode    ("3")
        , strIntCode    ("3")
        , strLayout     ("ABCDE-ABCDE")
        , strScribId    ("34567-01-A0")
        , strScribLot   ("00000024")
        //
        , fDiameter     (200.0)
        , fEdgeClearance(3.0)
        , dieSize       (5.5, 11.0)
        , dieGap        (2.0, 2.0)
        , maxColRow     (28, 14)
        , shOrientation (0)
        , shRefDieDir   (0)
        , shMapType     (0)
        , shNulBc       (0)
        , shNotch       (0)

        , vecRefDie     (3)
        , vecTargetDie  (2)

        , shMapId       (0)
        , shBincodeFormat (1)
    {
    };

} stMapInfo;


class CMitFbMap
{
public:
    CMitFbMap(void);
    ~CMitFbMap(void);

    bool LoadFbMap(std::string strFilename, std::vector<short> &vecMap);
    bool WriteFbMap(std::string strFilename, const std::vector<short> &vecMap);

    bool WriteTextMap(std::string strFilename, const std::vector<short> &vecMap);

    bool GetFbMapVector(std::vector<short> &vecMap);

    void GetInfo(stMapInfo &Info) { Info = m_stInfo; }
    void SetInfo(stMapInfo &Info) { m_stInfo = Info; }

private:
    bool serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb);
    bool deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf);

    void populateInfo();
    bool BasicInfoText(std::ofstream &outfile);

    std::unique_ptr<char> m_fbBuf;

    stMapInfo m_stInfo;

};

