#include <iostream>
#include <Windows.h>
#include <string>
#include <cmath>

using namespace std;

int main()
{
	ULARGE_INTEGER a;
	GetDiskFreeSpaceExA(NULL, NULL, &a, NULL);
	cout << round(a.QuadPart/(1024*1024*1024*1.0)) << endl;
	
}

