#pragma once

#include <string>
#include <vector>

#define MC_MESSAGE_SIZE_MAX 512

typedef struct _MC_MSG_GRP
{
    int  msgType;
    int  msgSize;
    char byteMsg[MC_MESSAGE_SIZE_MAX];
} MC_MSG_GRP;

typedef struct _MSG_DATA
{
    int  msgType;
    std::string strByteMsg;
} MC_DATA;

class CMsgDecode
{
public:
    CMsgDecode(void);
    ~CMsgDecode(void);

    bool getMsg(MC_DATA &msg);

    void appendPacket(const char *chStream, int size);
    void appendPacket(const std::string &strStream);
    void appendByte(char chByte) ;
    void resetBuf();

    std::string createMsg(int nType, const std::string &strMsg);

private:
    void discardPacket(size_t Len);
    int ReadInt32(const std::string &strBuf);
    std::string WriteInt32(int nData);

    std::string m_strBuf;
};

