#pragma once

#include "DNetResult.h"
#include "IPVer.h"
#include "consts.h"

namespace DNet
{
class EndPoint
{
  public:
    EndPoint() = default;
    EndPoint(const std::string &hostName, short port, IPVer ipversion = IPVer::IPV4);
    explicit EndPoint(const sockaddr_in &addr, IPVer IPVersion = IPVer::IPV4);
    EndPoint(const EndPoint &other) = default;
    EndPoint(EndPoint &&other) = default;
    EndPoint &operator=(const EndPoint &other) = default;
    EndPoint &operator=(EndPoint &&other) = default;
    ~EndPoint() = default;

    DNetResult resolve(const std::string &hostName, short port, IPVer ipversion = IPVer::IPV4);
    DNetResult resolveHostName(const std::string &IP, IPVer ipversion = IPVer::IPV4);
    void SetHostNameAndPort(const std::string &hostName, short port, IPVer ipversion = IPVer::IPV4);
    [[nodiscard]] IPVer GetIPVersion() const
    {
        return m_IPVersion;
    }
    [[nodiscard]] inline std::string GetHostName() const
    {
        return m_hostName;
    }
    [[nodiscard]] inline std::string GetIP() const
    {

        return m_hostIP;
    }
    [[nodiscard]] inline uint16_t GetPort() const
    {
        return m_port;
    }
    [[nodiscard]] sockaddr_in GetAddr() const;

    bool operator==(const EndPoint &other) const;
    bool operator!=(const EndPoint &other) const;

  private:
    std::string m_hostIP = "";
    std::string m_hostName = "";
    uint16_t m_port = 0;
    std::vector<byte> m_IPBinary = {};
    IPVer m_IPVersion = IPVer::IPNOTVALID;
    sockaddr_in m_addr = {};
    sockaddr_in6 m_addr6 = {};
};
} // namespace DNet
