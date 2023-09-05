#pragma once

namespace DNet
{
enum class DSockOptions
{
    NonBlocking = 1,
    ReuseAddr = 2,
    ReusePort = 4,
    NoDelay = 8,
    KeepAlive = 16,
    IPv6Only = 32,
};
} // namespace DNet
