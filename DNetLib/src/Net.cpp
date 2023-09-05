#include "Net.h"

namespace DNet {

	DNetResult Network::Initialize() {
		WSADATA wsaData;
		uint32_t res =  WSAStartup(MAKEWORD(2, 2), &wsaData);
		if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
			std::cerr << "Could not find a usable version of Winsock.dll" << std::endl;
			return DNetResult::DNetError;
		}
		if (res != 0) {
			uint32_t error = WSAGetLastError();
			return DNetResult::DNetError;
		}
		return DNetResult::DNetSuccess;
	}

	DNetResult Network::Shutdown() {
		uint32_t res = WSACleanup();
		if (res != 0) {
			uint32_t error = WSAGetLastError();
			return DNetResult::DNetError;
		}
		return DNetResult::DNetSuccess;
	}
} // namespace Net

