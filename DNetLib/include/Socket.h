#pragma once
#include "EndPoint.h"
#include "consts.h"

namespace DNet
{
class DSocket
{
  public:
    explicit DSocket(IPVer IPVersion = IPVer::IPV4);
    DSocket(SOCKETHandler sokcet, IPVer IPVersion = IPVer::IPV4);
    DSocket(const EndPoint &endPoint, IPVer IPVersion = IPVer::IPV4);
    DSocket(const EndPoint &endPoint, SOCKETHandler sokcet, IPVer IPVersion = IPVer::IPV4);
    DSocket(const DSocket &) = delete;
    DSocket(DSocket &&);
    DSocket operator=(DSocket &&);
    DSocket &operator=(const DSocket &) = delete;
    ~DSocket();

    DNetResult Create(IPVer IPVersion);
    DNetResult Bind(const EndPoint &endPoint);
    DNetResult Listen();
    DSocket Accept();
    DNetResult Connect(const EndPoint &endPoint);
    DNetResult SendHello();
    DNetResult Send(const char *buffer, int len);
    uint16_t Recv();
    DNetResult Close();

    DNetResult SetNonBlocking(bool nonBlocking);
    DNetResult SetSendBufferSize(int size);
    DNetResult SetRecvBufferSize(int size);

    inline bool IsValid() const
    {
        return m_socket != INVALID_SOCKET;
    }
    [[nodiscard]] inline std::vector<char> GetBuffer() const
    {
        return m_buffer;
    }
    bool IsNonBlocking() const;
    bool IsReuseAddr() const;
    bool IsNoDelay() const;
    bool IsKeepAlive() const;
    int GetSendBufferSize() const;
    int GetRecvBufferSize() const;

    inline [[nodiscard]] EndPoint GetLocalEndPoint() const
    {
        return m_localEndPoint;
    }

  private:
    EndPoint m_localEndPoint;
    SOCKETHandler m_socket = INVALID_SOCKET;
    IPVer m_IPVersion = IPVer::IPV4;
    std::vector<char> m_buffer;
};
} // namespace DNet
