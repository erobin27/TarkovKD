#pragma once
std::string readCharString(DWORD64 address, int length);
std::wstring readWCharString(DWORD64 address, int length);
std::string wstring_to_string(const std::wstring& wstr);
bool loopThroughList(uint64_t addr, int count);
void entityLoop();