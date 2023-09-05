#pragma once

namespace DNet {
	namespace Helper {
		
		void trimLeft(std::string& str) {
			str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
				return !(std::isspace(ch) || ch == '\n' || ch == '\0');
			}));
		}

/*
		void trimRight(std::string& str) {
			str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
				return !(std::isspace(ch) || ch == '\n' || ch == '\0');
			}).base(), str.end());
		}
*/
		// This function is used to convert a wstring to a string
		/*std::string wstringToString(const std::wstring& wstr) {
			std::string str(wstr.begin(), wstr.end());
			return str;
		}*/
		// This function is used to convert a string to a wstring
/*
		std::wstring stringToWstring(const std::string& str) {
			std::wstring wstr(str.begin(), str.end());
			return wstr;
		}
*/
		// This is used to convert the IP address to a wstring
/*
		std::wstring ipToString(const sockaddr_in& addr) {
			return std::to_wstring(addr.sin_addr.S_un.S_un_b.s_b1) + L"." + 
												std::to_wstring(addr.sin_addr.S_un.S_un_b.s_b2) + 
												L"." + std::to_wstring(addr.sin_addr.S_un.S_un_b.s_b3) + 
												L"." + std::to_wstring(addr.sin_addr.S_un.S_un_b.s_b4);
;
		}
*/
		// This is used to convert the port to a wstring
/*
		std::wstring portToString(const sockaddr_in& addr) {
			std::wstring port = std::to_wstring(addr.sin_port);
			return port;
		}
*/
		// This is used to convert the message to a wstring
		// This is used to convert the username to a wstring
		// This is used to convert the passw
	}

}
