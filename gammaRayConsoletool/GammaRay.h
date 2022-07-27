#include "BIUSB.H"
#include "miKeySender.h"
#include <string>
#include <iostream>

#define GROFFLINE		FALSE
#define GRONLINE		TRUE
#define INPUTBITSLONGS		4

struct key2send
{
	char keyOnPress;
	bool shiftPress;
	bool ctrlPress;
	bool altPress;
	bool holdPress;
	char keyOnRelease;
	bool shiftRelease;
	bool ctrlRelease;
	bool altRelease;
};


#pragma once
class GammaRay
{
public:
	GammaRay() { this->initialize();}
	~GammaRay() { 		
		BOOL retval = CloseDevices(DeviceCount, &DeviceList[0]); 
		std::cout << "Destructor called";
	}

	void detectGR();
	void checkDataUpdate();
	void outputBoardData();
	std::string getDataBuffer();
	std::string getDataBufferOld();
	BOOL isOnline();  // returns true, if GammaRay is connected 	
	
	BOOL loadConfigFile(std::string filepath);


private:	
	DeviceStatus	DeviceStatus[1];
	DeviceParam		DeviceList[1];
	UINT			DeviceCount;
	char			DataBuffer[256];
	char			DataBufferOld[256];

	key2send config[256];

	BOOL online = FALSE;
	std::string configFile;
	
	std::string keyCommands[MAX_INPUTS] = { "VK_NUMPAD0", "a"};
	//miKeySender	keySender; // = new miKeySender();

	void initialize();
	void sendKeystroke();	
	void parseConfigFile();
	void writeLog();

	
};

