#pragma once

#include "..\..\schema\ultINFO_generated.h"

#include <string>

class CFbUltInfo
{
public:
    CFbUltInfo(void);
    ~CFbUltInfo(void);

    bool Load(std::string strFilename, std::vector<ultINFO::stUnit> &vecUnits);
    bool Save(std::string strFilename, std::vector<ultINFO::stUnit> &vecUnits);

    bool SaveToMem(char *pBaseMem, size_t size, std::vector<ultINFO::stUnit> &vecUnits);
    bool LoadFromMem(char *pBaseMem, size_t size, std::vector<ultINFO::stUnit> &vecUnits);

private:
    bool serialize(std::string strFilename, flatbuffers::FlatBufferBuilder &fbb);
    bool deserialize(std::string strFilename, std::unique_ptr<char>& fbbBuf);


};

