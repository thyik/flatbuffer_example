#pragma once

#include "..\..\schema\turretINFO_generated.h"

#include <string>

class CFbTurretInfo
{
public:
    CFbTurretInfo(void);
    ~CFbTurretInfo(void);

    bool Load(std::string strFilename, std::vector<turretINFO::stStnInfo> &vecStn);
    bool Save(std::string strFilename, std::vector<turretINFO::stStnInfo> &vecStn);

    bool SaveToMem(char *pBaseMem, size_t size, std::vector<turretINFO::stStnInfo> &vecStn);
    bool LoadFromMem(char *pBaseMem, size_t size, std::vector<turretINFO::stStnInfo> &vecStn);

private:
    bool serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb);
    size_t deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf);


};

