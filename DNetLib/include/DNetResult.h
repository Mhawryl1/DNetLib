#pragma once

namespace DNet
{

enum DNetResult
{
    DNetSuccess = 0,
    DNetError = -1,
    DNetSOCKET_ALREADY_CREATED = -2,
    DNetSOCKET_CREATE_FAILED = -3,
    DNetSOCKET_CONNECT_FAILED = -4,
    DNetSOCKET_CLOSE_FAILED = -4,
    DNetSOCKET_BIND_FAILED = -5,
    DNetSOCKET_LISTEN_FAILED = -6,
    DNetSOCKET_SEND_FAILED = -7,
    DNetSOCKET_RECV_FAILED = -8,
};

} // namespace DNet
