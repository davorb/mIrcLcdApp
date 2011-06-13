// SerialLogParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int _tmain(int argc, char* argv[])
{
	HANDLE hSerial;
	DWORD bytesWritten;
	LPCWSTR portName = L"COM3";
	hSerial=CreateFile(portName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if(hSerial == INVALID_HANDLE_VALUE)
		return 1;

	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	SetCommState(hSerial, &dcbSerialParams);

	char buffer[255];

	FILE *fp = fopen("lcddata.txt", "r");
	char output[1024];
	int i=0, c;
	while ((output[i++] = getc(fp)) != EOF)
		;
	output[i] = '\0';

	if(WriteFile(hSerial, output, strlen(output), &bytesWritten, NULL) == 0) {
		printf("Failed to write to serial port.\n");
	}
	Sleep(2000);
	return 0;
}

