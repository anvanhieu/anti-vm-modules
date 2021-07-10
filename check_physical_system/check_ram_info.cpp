//references: https://stackoverflow.com/questions/5553665/get-ram-system-size/5557541#5557541

#define _WIN32_WINNT  0x0501 
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
	cout << "[+] Check RAM Size less than 4GB => ";

	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	
	GlobalMemoryStatusEx (&statex);
	int RAM_size = round((float)statex.ullTotalPhys/(1024*1024*1024));
	cout << RAM_size << endl;

	if (RAM_size < 4)
		cout << "Could be VM" << endl;
	else
		cout << "OK" << endl;
	return EXIT_SUCCESS;
}