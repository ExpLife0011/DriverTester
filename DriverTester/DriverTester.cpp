// DriverTester.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

using namespace std;

int main(int argc, char* argv[])
{
	HANDLE handle;
	BOOL bResult = false;
	string driverName;
	DWORD ioctl = 0;
	INT bufferIn = 0;
	DWORD bufferInSize = 0;
	LPVOID bufferOut = NULL;
	DWORD bufferOutSize = 0;
	DWORD dwBytes = 0;

	// clear creen
	system("cls");

	// check number of arguments
	if (argc < 3 || argc > 4) {
		cout << "[-] Too few arguments. Usage: DriverTester.exe drivername ioctl [buffer]" << endl;
		return -1;
	}

	// parse arguments
	driverName = "\\\\.\\" + string(argv[1]);
	ioctl = strtoul(argv[2], 0, 16);
	if (argc == 4) {
		bufferIn = atoi(argv[3]);
		bufferInSize = sizeof(bufferIn);
	}

	// connect to device
	handle = CreateFileA(driverName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handle == INVALID_HANDLE_VALUE) {
		cout << "[-] Couldn't obtain a handle to the Device." << endl;
		return -2;
	}

	// send IOCTL to the driver
	bResult = DeviceIoControl(handle, ioctl, &bufferIn, bufferInSize, bufferOut, bufferOutSize, &dwBytes, NULL);

	if (bResult == NULL) {
		CloseHandle(handle);
		cout << "[-] DeviceIoControl failed!" << endl;
		return -3;
	}

	// close handle
	CloseHandle(handle);

	// wait for char and exit
	cout << "[+] DeviceIoControl sucess! Press any key to exit." << endl;
	getchar();

	return 0;
}

