#include "BIUSB.H"
#include "miKeySender.h"
#include "GRConfig.h"
#include <string>
#include <iostream>

#define GROFFLINE		FALSE
#define GRONLINE		TRUE
#define INPUTBITSLONGS		4

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

	BOOL online = FALSE;
	std::string configFile;
	GRConfig config;
	
	std::string keyCommands[MAX_INPUTS] = { "VK_NUMPAD0", "a"};
	//miKeySender	keySender; // = new miKeySender();

	void initialize();
	void sendKeystroke();	
	void parseConfigFile();
	void writeLog();

	
};

