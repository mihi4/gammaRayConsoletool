// gammaRayConsoletool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BIUSB.H"
#include "GammaRay.h"

// #include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

BOOL quit = FALSE;
DWORD timerInterval = 200;
DWORD timerInterval2 = 2000;
GammaRay gammaRay;

void timertick(int count)  // first timer function, to update the inputs every timerInterval ms.
{
	char buff[64];
	_itoa_s(count, buff, 64, 10);
	char grOnline = (gammaRay.isOnline()) ? 'Y' : 'N';
	string dataBuffer = gammaRay.getDataBuffer();
	string dataBufferOld = gammaRay.getDataBufferOld();
	//printf("\033c");
	//cout << dataBuffer << "\n" << dataBufferOld << "\n";

}

void timertick2(int count)  // second timer function to check, if gammaray is still here
{
	char buff[64];
	_itoa_s(count, buff, 64, 10);
	//cout << "xx" << buff << "xx";
	if (!gammaRay.isOnline()) {
		cout << "GammaRay is disconnected or unavailable!\n";
		gammaRay.detectGR();
	}

}

DWORD WINAPI thread2(__in LPVOID lpParameter) {
	int nCount = 0;
	HANDLE hTimer = CreateEvent(NULL, FALSE, FALSE, NULL);
	while (!quit)
	{

		WaitForSingleObject(hTimer, timerInterval2);
		//cout << "1 s\n";
		nCount++;
		timertick2(nCount);

	}
	return 0;
}
DWORD WINAPI thread1(__in LPVOID lpParameter) {
	int nCount = 0;
	HANDLE hTimer = CreateEvent(NULL, FALSE, FALSE, NULL);
	while (!quit)
	{
		
		WaitForSingleObject(hTimer, timerInterval);
		//cout << "1 s\n";
		nCount++;
		timertick(nCount);

	}
	return 0;
}

int main()
{
    std::cout << "GammaRay started. Press Return to quit!\n";
	gammaRay.detectGR();
	if (gammaRay.isOnline()) {
		gammaRay.outputBoardData();
	}

	Sleep(2500);
	printf("\033c");

	DWORD threadID1;
	DWORD threadID2;

	HANDLE h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread1, 0, 0, &threadID1);
	HANDLE h2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread2, 0, 0, &threadID2);

	int dummy = getchar();
	quit = TRUE;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
