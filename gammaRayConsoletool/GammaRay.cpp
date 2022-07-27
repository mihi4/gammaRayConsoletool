#include "GammaRay.h"
#include <iostream>

using namespace std;

void GammaRay::initialize()
{	
	memset(DataBuffer, 0, MAX_INPUTS);
	memset(DataBufferOld, 0, MAX_INPUTS);
}

void GammaRay::detectGR()
{
	cout << "in detectGR\n";

	if (!DetectDevice(&this->DeviceCount, this->DeviceList, PID_GAMMARAY, DT_HID)) {
		this->online = GROFFLINE;
		return;
	}
	LONG retval = ReadInputData(&DeviceList[0], DataBuffer, FALSE);
	this->online = GRONLINE;
}

BOOL GammaRay::isOnline() {
	return this->online;
}

std::string GammaRay::getDataBuffer() {

	int i;
	string str, str2;

	this->checkDataUpdate();

	for (i = 0; i < MAX_INPUTS; i++) {
		str2 = (this->DataBuffer[i] ? "1_" : "0_");
		str.append(str2);
	}

	return str;
}

std::string GammaRay::getDataBufferOld() {

	int i;
	string str, str2;

	this->checkDataUpdate();

	for (i = 0; i < MAX_INPUTS; i++) {
		str2 = (this->DataBufferOld[i] ? "1_" : "0_");
		str.append(str2);
	}

	return str;
}

void GammaRay::outputBoardData() {
	char buff[64];
	//_itoa_s(count, buff, 64, 10)
	cout << "Name: " << (this->DeviceList[0].DeviceName) << " Serial: " << (this->DeviceList[0].SerialNum) << " Version: " << _itoa_s(this->DeviceList[0].VersionNumber, buff, 10) << "\n" << " DevPath: " << this->DeviceList[0].DevicePath << "\n"
		<< "InputIndices: " << _itoa_s(this->DeviceList[0].NumberInputIndices, buff, 10) << " PortIndices: " << _itoa_s(this->DeviceList[0].NumberPortIndices, buff, 10) << "\n"
		<< "OutputIndices: " << _itoa_s(this->DeviceList[0].NumberOutputIndices, buff, 10) << " LatchIndices: " << _itoa_s(this->DeviceList[0].NumberLatchedIndices, buff, 10) << "\n"
		<< " Manufacturer: " << (this->DeviceList[0].ManufName) << "\n";
}

BOOL GammaRay::loadConfigFile(std::string filepath) {
	cout << "trying to load config file " << filepath << "\n";
	return TRUE;
}

void GammaRay::checkDataUpdate() {

	LONG retval;
	int i;
	string str, str2;
	char buff[64];
	size_t bufSize = sizeof(DataBufferOld);

	retval = ReadInputData(&DeviceList[0], DataBuffer, FALSE);
			
	switch (retval) {
	case DEV_WAIT:
		memcpy(DataBufferOld, DataBuffer, bufSize);
		// nothing to do but wait...		
		break;

	case DEV_INPUT:
		// new data returned.
		// loop through inputs and look for any toggled inputs.
		// for (i = 0; i < DeviceList[0].NumberInputIndices; i++) 

		if (!(memcmp(DataBuffer, DataBufferOld, bufSize) == 0)) {
			cout << "Inputbuffer has changed!\n";
		
			for (i = 0; i < MAX_INPUTS; i++) {
				if (DataBuffer[i] != DataBufferOld[i]) {					
					//string statusOld = new string (DataBufferOld[i]); // ? "ON to " : "OFF to ");
					//string statusNew = DataBuffer[i]; // ? "ON" : "OFF");
					cout << "#:" << i << "-" << +DataBufferOld[i] << " to " << +DataBuffer[i] << "\n";
					//str.Format("%s - Input %d : %s\r\n%s", DeviceList[m_DeviceIndex].DeviceName, i + 1, (DataBuffer[i] ? "ON" : "OFF"), str2);
					//m_InputsPage.SetWindowText(str);
				}
			}
		}
		memcpy(DataBufferOld, DataBuffer, bufSize);
		break;

	case DEV_TIMEOUT:
		// something went wrong. The device may be inoperable or disconnected
		//timeval = 0;
		std::cout << "ERROR: timeout occured!";
		this->online = GROFFLINE;
		break;
	}

	return;
}



/*void GammaRay::updateData() {
	// insert code to read data from GR and compare to previous value
	//
	// then call parsing function to see if any press/release functions are configured.
	// finally call function to send appropriate keystrokes
	



	return;
} */





