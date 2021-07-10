#include <iostream>
#include <intrin.h>
#include <string>

using namespace std;

string VMware = "VMware";

int main()
{
	__cpuid(CPUInfo, 0x40000000);
	for(auto & info : CPUInfo){
		string s = (char*)&info;
		
		if(s.find(VMware) != string::npos)
		{
			cout << "VMware detected" << endl;
			break;
		}
	} 
	
	return 0;
}
