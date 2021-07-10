#include <iostream>
#include <Windows.h>

#define MIN_NUMBER_PROCESSOR_CORE 2

using namespace std;

int main()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	int numCPU = sysinfo.dwNumberOfProcessors;
	cout << numCPU << endl;
	if (numCPU < MIN_NUMBER_PROCESSOR_CORE)
		cout << "Could be VM";
	else
		cout << "OK";
	
	return 0;
}