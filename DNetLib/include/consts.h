#pragma once
#include "pch.h"

namespace DNet
{
using byte = uint8_t;
#ifdef _WIN32
using SOCKETHandler = SOCKET;
#endif
} // namespace DNet
