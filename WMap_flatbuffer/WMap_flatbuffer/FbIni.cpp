#include "StdAfx.h"
#include "FbIni.h"

#include "..\..\schema\mit_fbini_generated.h"

#include <fstream>
#include <iostream>

using namespace MitFBINI;

CFbIni::CFbIni(void)
{
}


CFbIni::~CFbIni(void)
{
}

bool CFbIni::Load(std::string strFilename)
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

    auto fileini = GetFBINI(buf2.get());

    if (fileini->item() == nullptr)
        return false;

    std::cout << std::endl;
    std::cout << '[' << fileini->section()->str() << ']';
    std::cout << std::endl;

    for (auto it = fileini->item()->begin();
        it != fileini->item()->end();
        ++it)
    {
        std::cout << it->key()->str();
        std::cout << '=';
        std::cout << it->strValue()->str();
        std::cout << std::endl;

    }

    return true;
}

bool CFbIni::Save(std::string strFilename)
{
    flatbuffers::FlatBufferBuilder builder;

    std::vector<flatbuffers::Offset<KEYVALUE>> mlocVector;
    
    
    auto section = builder.CreateString("Section001");
    auto key     = builder.CreateString("Key001");
    auto value   = builder.CreateString("0.123");
    //
    // create inner table
    mlocVector.push_back(CreateKEYVALUE(builder, key, value));

    mlocVector.push_back(CreateKEYVALUE(builder, builder.CreateString("Key002"), builder.CreateString("2.123")));
    mlocVector.push_back(CreateKEYVALUE(builder, builder.CreateString("Key003"), builder.CreateString("0.323")));
    
    auto keyValue = builder.CreateVector(mlocVector);

    // create root table
    auto file = CreateFBINI(builder, section, keyValue);

    builder.Finish(file);
    //
    size_t size = builder.GetSize();

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

std::string CFbIni::GetString(std::string strKey)
{
    return "";
}

long        CFbIni::GetLong(std::string strKey)
{
    return 0L;
}

double      CFbIni::GetDouble(std::string strKey)
{
    return 0.0;
}

void CFbIni::WriteString(std::string strKey, std::string strValue)
{
}

void        CFbIni::WriteLong(std::string strKey, long lValue)
{
}

void      CFbIni::WriteDouble(std::string strKey, double dValue)
{
}