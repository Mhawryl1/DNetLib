#include "EndPoint.h"

using namespace DNet;

EndPoint::EndPoint(const std::string &host, short port, IPVer IPVersion)
{
    SetHostNameAndPort(host, port, IPVersion);
}
EndPoint::EndPoint(const sockaddr_in &addr, IPVer IPVersion) : m_addr(addr), m_IPVersion(IPVersion)
{
    m_port = ntohs(addr.sin_port);
    m_hostIP.resize(m_IPVersion == IPVer::IPV4 ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
    inet_ntop(m_IPVersion == IPVer::IPV4 ? AF_INET : AF_INET6, &addr.sin_addr, m_hostIP.data(),
              m_IPVersion == IPVer::IPV4 ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
}
DNetResult EndPoint::resolve(const std::string &host, short port, IPVer IPVersion)
{
    addrinfo *result = nullptr;
    addrinfo hints = {};

    memset(&hints, 0, sizeof(hints));
    uint32_t res = 0;
    std::string ip;
    switch (IPVersion)
    {
    case IPVer::IPV4:
        hints.ai_family = AF_INET;
        // function resolve host name to IP address
        res = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &result);
        if (res != 0)
        {
            const uint32_t error = WSAGetLastError();
            return DNetResult::DNetError;
        }
        m_addr = *(sockaddr_in *)result->ai_addr;
        ip.resize(result->ai_addrlen);
        m_IPBinary.resize(result->ai_addrlen);
        std::memcpy(&m_IPBinary[0], &m_addr.sin_addr, result->ai_addrlen);
        if (inet_ntop(AF_INET, &m_addr.sin_addr, ip.data(), result->ai_addrlen) == NULL)
        {
            const int32_t error = WSAGetLastError();
            return DNetResult::DNetError;
        }
        m_hostName = host;
        m_IPVersion = IPVer::IPV4;
        break;
    case IPVer::IPV6:
        hints.ai_family = AF_INET6;
        res = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &result);
        if (res != 0)
        {
            const uint32_t error = WSAGetLastError();
            return DNetResult::DNetError;
        }

        m_addr6 = *(sockaddr_in6 *)result->ai_addr;
        m_IPBinary.resize(result->ai_addrlen);
        ip.reserve(result->ai_addrlen);
        if (inet_ntop(AF_INET6, &m_addr6.sin6_addr, ip.data(), result->ai_addrlen) == NULL)
        {
            const uint32_t error = WSAGetLastError();
            return DNetResult::DNetError;
        }
        m_hostName = host;
        m_IPVersion = IPVer::IPV6;
        break;
    default:
        break;
    }

    freeaddrinfo(result);

    return DNetResult::DNetSuccess;
}

DNetResult EndPoint::resolveHostName(const std::string &IP, IPVer IPVersion /*= IPVer::IPV4*/)
{
    sockaddr_in addr = {};
    sockaddr_in6 addr6 = {};
    m_hostName.reserve(NI_MAXHOST);
    switch (IPVersion)
    {
    case IPVer::IPV4:
        addr.sin_family = AF_INET;
        inet_pton(AF_INET, IP.c_str(), &addr.sin_addr);
        if (getnameinfo((sockaddr *)&addr, sizeof(addr), m_hostName.data(), m_hostName.capacity(), NULL, NULL,
                        NI_NUMERICSERV) != NULL)
        {
            const int32_t error = WSAGetLastError();
            return DNetResult::DNetError;
        }

        return DNetResult::DNetSuccess;
        break;
    case IPVer::IPV6:
        addr6.sin6_family = AF_INET6;
        inet_pton(AF_INET6, IP.c_str(), &addr6.sin6_addr);
        if (getnameinfo((sockaddr *)&addr6, sizeof(addr6), m_hostName.data(), m_hostName.capacity(), NULL, NULL,
                        NI_NAMEREQD) != NULL)
        {
            const int32_t error = WSAGetLastError();
            return DNetResult::DNetError;
        }

        return DNetResult::DNetSuccess;
        break;
    default:
        break;
    }
}
void EndPoint::SetHostNameAndPort(const std::string &host, short port, IPVer IPVersion /*= IPVer::IPV4*/)
{
    in_addr addr = {};               // place holder for IPv4 address
    in_addr6 addr6 = {};             // place holder for IPv6 address
    m_IPVersion = IPVer::IPNOTVALID; // if IPVersion stay IPNOTVALID, it means host is not valid IP address
    m_port = port;
    switch (IPVersion)
    {
    case IPVer::IPV4:

        if (inet_pton(AF_INET, host.c_str(), &addr) ==
            1) // if true convert IP to binary representation end with success
        {
            if (addr.S_un.S_addr != INADDR_NONE)
            {
                m_addr.sin_family = AF_INET;
                m_addr.sin_port = htons(port);
                m_addr.sin_addr = addr;
                m_IPBinary.resize(sizeof(ULONG));
                std::memcpy(&m_IPBinary[0], &addr.S_un.S_addr, sizeof(ULONG));
                m_hostIP = host;
                m_IPVersion = IPVer::IPV4;
            }
        }
        else // if false, host is not IP address, resolve host name
        {

            const int32_t error = WSAGetLastError();
            resolve(host, port, IPVersion);
        }

        break;
    case IPVer::IPV6:
        if (inet_pton(AF_INET6, host.c_str(), &addr6) == 1) // if true convert IP to binary representation success
        {
            m_IPBinary.resize(16);
            std::memcpy(&m_IPBinary[0], &addr6.u.Byte, 16);
            m_hostIP = host;
            m_IPVersion = IPVer::IPV6;
        }
        else // if false, host is not IP address, resolve host name
        {

            const int32_t error = WSAGetLastError();
            resolve(host, port, IPVersion);
        }
        break;
    default:
        break;
    }
}

sockaddr_in EndPoint::GetAddr() const
{
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    std::memcpy(&addr.sin_addr, m_IPBinary.data(), sizeof(ULONG));

    return addr;
}

bool EndPoint::operator==(const EndPoint &other) const
{
    return this == &other;
}

bool EndPoint::operator!=(const EndPoint &other) const
{
    return this != &other;
}
