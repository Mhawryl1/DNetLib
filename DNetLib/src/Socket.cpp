#include "Socket.h"

namespace DNet
{

DSocket::DSocket(IPVer IPVersion) : m_IPVersion(IPVersion)
{
}

DSocket::DSocket(SOCKETHandler sokcet, IPVer IPVersion) : m_socket(sokcet), m_IPVersion(IPVersion)
{
    Create(IPVersion);
}

DSocket::DSocket(const EndPoint &endPoint, IPVer IPVersion) : m_localEndPoint(endPoint), m_IPVersion(IPVersion)
{
    Create(IPVersion);
}

DSocket::DSocket(DSocket &&other)
{
    m_IPVersion = other.m_IPVersion;
    other.m_IPVersion = IPVer::IPNOTVALID;
    // TODO: move constructor EndPoint class
    m_localEndPoint = other.m_localEndPoint;
    m_socket = other.m_socket;
    other.m_socket = INVALID_SOCKET;
}

DSocket::DSocket(const EndPoint &endPoint, SOCKETHandler sokcet, IPVer IPVersion /*= IPVer::IPV4*/)
    : m_localEndPoint(endPoint), m_socket(sokcet), m_IPVersion(IPVersion)
{
}

DSocket DSocket::operator=(DSocket &&)
{
    // TODO: move operator=
    return DSocket();
}
DSocket::~DSocket()
{
    Close();
}

DNetResult DSocket::Create(IPVer IPVersion)
{
    if (m_socket != INVALID_SOCKET)
    {
        return DNetResult::DNetSOCKET_ALREADY_CREATED;
    }

    switch (IPVersion)
    {
    case IPVer::IPV4:
        m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        break;
    case IPVer::IPV6:
        m_socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
        break;
    default:
        break;
    }

    if (m_socket == INVALID_SOCKET)
    {
        uint32_t error = WSAGetLastError();
        return DNetResult::DNetSOCKET_CREATE_FAILED;
    }
    return DNetResult::DNetSuccess;
}

DNetResult DSocket::Bind(const EndPoint &endPoint)
{
    sockaddr_in addr = endPoint.GetAddr();
    if (bind(m_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr)) == SOCKET_ERROR)
    {
        uint32_t error = WSAGetLastError();
        Close();
        return DNetResult::DNetSOCKET_BIND_FAILED;
    }
    return DNetResult::DNetSuccess;
}

DNetResult DSocket::Listen()
{
    if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        uint32_t error = WSAGetLastError();
        Close();
        return DNetResult::DNetSOCKET_LISTEN_FAILED;
    }
    return DNetResult();
}

DSocket DSocket::Accept()
{
    sockaddr_in addr = {}; // to store new connection info
    int addrLen = sizeof(sockaddr_in);
    SOCKETHandler newSocket = accept(m_socket, (sockaddr *)&addr, &addrLen);
    if (newSocket == INVALID_SOCKET)
    {
        uint32_t error = WSAGetLastError();
        return DNetResult::DNetError;
    }
    return std::move(DSocket(EndPoint(addr), newSocket, m_IPVersion));
}

DNetResult DSocket::Connect(const EndPoint &endPoint)
{
    sockaddr_in addr = endPoint.GetAddr();
    if (connect(m_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr)) == SOCKET_ERROR)
    {
        uint32_t error = WSAGetLastError();
        return DNetResult::DNetSOCKET_CONNECT_FAILED;
        Close();
    }

    return DNetResult::DNetSuccess;
}

DNetResult DSocket::SendHello()
{
    std::string hello = "[ok signal] Hallo from server.";

    if (send(m_socket, hello.c_str(), (int)hello.size(), 0) == SOCKET_ERROR)
    {
        uint32_t error = WSAGetLastError();
        return DNetResult::DNetSOCKET_SEND_FAILED;
    }
    return DNetResult::DNetSuccess;
}

DNetResult DSocket::Send(const char *buffer, int len)
{
    uint32_t bytesSend = 0;
    // TODO: send
    return [&, this]() -> DNetResult {
        while (bytesSend < len)
        {
            int sendResult = send(m_socket, buffer + bytesSend, len - bytesSend, 0);
            if (sendResult == SOCKET_ERROR)
            {
                uint32_t error = WSAGetLastError();
                return DNetResult::DNetSOCKET_SEND_FAILED;
            }
            bytesSend += sendResult;
        }
        return DNetResult::DNetSuccess;
    }();
}

uint16_t DSocket::Recv()
{
    m_buffer.clear();
    m_buffer.resize(4096);
    uint16_t bytesRead = recv(m_socket, m_buffer.data(), 4096, MSG_WAITALL);
    if (bytesRead == SOCKET_ERROR)
    {
        uint32_t error = WSAGetLastError();
        return DNetResult::DNetSOCKET_RECV_FAILED;
    }
    m_buffer.resize(bytesRead);
    return DNetResult::DNetSuccess;
}

DNetResult DSocket::Close()
{
    if (closesocket(m_socket) != NULL)
    {
        uint32_t error = GetLastError();
        return DNetResult::DNetSOCKET_CLOSE_FAILED;
    }
    m_socket = INVALID_SOCKET;
    return DNetResult::DNetSuccess;
}

DNetResult DSocket::SetNonBlocking(bool nonBlocking)
{
    // TODO: set non blocking
    return DNetResult();
}

DNetResult DSocket::SetSendBufferSize(int size)
{
    // TODO: set send buffer size
    return DNetResult();
}

DNetResult DSocket::SetRecvBufferSize(int size)
{
    // TODO : set recv buffer size
    return DNetResult();
}

bool DSocket::IsNonBlocking() const
{
    return false;
}

bool DSocket::IsReuseAddr() const
{
    return false;
}

bool DSocket::IsNoDelay() const
{
    return false;
}

bool DSocket::IsKeepAlive() const
{
    return false;
}

int DSocket::GetSendBufferSize() const
{
    return 0;
}

int DSocket::GetRecvBufferSize() const
{
    return 0;
}

} // namespace DNet
