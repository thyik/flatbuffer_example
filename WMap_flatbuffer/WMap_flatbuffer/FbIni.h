#pragma once

#include <string>

class CFbIni
{
public:
    CFbIni(void);
    ~CFbIni(void);

    bool Load(std::string strFilename);
    bool Save(std::string strFilename);

    std::string GetString(std::string strKey);
    long        GetLong(std::string strKey);
    double      GetDouble(std::string strKey);

    void WriteString(std::string strKey, std::string strValue);
    void WriteLong(std::string strKey, long lValue);
    void WriteDouble(std::string strKey, double dValue);

};

