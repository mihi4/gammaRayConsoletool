#pragma once
#include <string>
#include <iostream>

struct key2send
{
	char keyOnPress = 0x0;
	bool shiftPress = false;
	bool ctrlPress = false;
	bool altPress = false;
	bool holdPress = false;
	char keyOnRelease = 0x0;
	bool shiftRelease = false;
	bool ctrlRelease = false;
	bool altRelease = false;
};


class GRConfig
{
public:
	GRConfig() {
		config[0].keyOnPress = 0x40; // A
	}
	void readConfigFile(std::string filepath);
	key2send getConfigValue(int index);

private:
	key2send config[256];
};

