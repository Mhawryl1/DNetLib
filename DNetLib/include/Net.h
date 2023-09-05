#pragma once
#include "EndPoint.h"

namespace DNet
{

class Network
{
  public:
    static DNetResult Initialize();
    static DNetResult Shutdown();

  private:
    WSAData m_wsaData;
};
} // namespace DNet
