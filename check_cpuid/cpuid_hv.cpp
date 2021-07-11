#include <iostream>
#include <intrin.h>
#include <string>

using namespace std;

int main()
{
	int CPUInfo[4] = { -1 };
	__cpuid(CPUInfo, 1);
	if ((CPUInfo[2] >> 31) & 1) 
	{
        cout << "Is hypervisor!" << endl;
    }

	return 0;
}

