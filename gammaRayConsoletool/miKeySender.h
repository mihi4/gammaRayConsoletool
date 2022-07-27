#pragma once

#include <Windows.h>
#include <string>

class miKeySender
{
public:
	miKeySender() { };
	~miKeySender() { };

	USHORT sendOutputs();

private: 
	USHORT sendKeyCommand(std::string command);
};

