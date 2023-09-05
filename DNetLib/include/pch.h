#include <algorithm>
#include <assert.h>
#include <cctype>
#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <windef.h>
#include <ws2tcpip.h>
#endif // _WIN32
