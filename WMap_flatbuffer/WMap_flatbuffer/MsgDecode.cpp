#include "StdAfx.h"
#include "MsgDecode.h"

const int RESERVE_MAX_BYTE = 512 ;

union convertByte2Int{
    int intData;
    char c[4];
};

CMsgDecode::CMsgDecode(void)
{
    // reserve for optimisation
    m_strBuf.reserve(RESERVE_MAX_BYTE);
}

CMsgDecode::~CMsgDecode(void)
{
    m_strBuf.clear();
}

std::string CMsgDecode::WriteInt32(int nData)
{
    convertByte2Int convert;  // to review endianess
    convert.intData = nData;
    size_t size = sizeof(int);

    std::string strBuf(convert.c, size);
    return strBuf;
}

std::string CMsgDecode::createMsg(int nType, const std::string &strMsg)
{
    std::string strBuf;
    strBuf.reserve(50);  // reserve to avoid reallocation when appeding

    strBuf += WriteInt32(nType);
    strBuf += WriteInt32(strMsg.size());
    strBuf += strMsg;

    return strBuf;
}

void CMsgDecode::resetBuf() 
{ 
    m_strBuf.clear(); 
}

void CMsgDecode::appendByte(char chByte) 
{ 
    m_strBuf.push_back(chByte); 
}

void CMsgDecode::appendPacket(const char *chStream, int size) 
{ 
    m_strBuf.append(chStream, size); 
}

void CMsgDecode::appendPacket(const std::string &strStream) 
{ 
    m_strBuf += strStream; 
}

void CMsgDecode::discardPacket(size_t Len) 
{
    m_strBuf.erase(0, Len);
}

int CMsgDecode::ReadInt32(const std::string &strBuf)
{
    convertByte2Int convert;  // to review endianess
    size_t size = sizeof(int);

    strBuf.copy(convert.c, size);

    return convert.intData;
}

bool CMsgDecode::getMsg(MC_DATA &msg)
{
    size_t sizeInt = sizeof(int);
    size_t nFixedLen = 2 * sizeInt;

    if (m_strBuf.size() < nFixedLen) // not enough data
        return false;

    msg.msgType = ReadInt32(m_strBuf.substr(0, sizeInt));

    int nMsgSize = ReadInt32(m_strBuf.substr(sizeInt, sizeInt));

    size_t BufMsgSize = m_strBuf.size() - nFixedLen;

    if (BufMsgSize < nMsgSize) 
    {
        // only partial message received.. wait for more data
        return false;
    }

    // extract message
    msg.strByteMsg = m_strBuf.substr(nFixedLen, nMsgSize);

    // discard processed packet frame
    discardPacket(nFixedLen + nMsgSize);
   
    return true;
}
