#include <iostream>
#include <Windows.h>
#include <string>
#include <cmath>

#define DISK_VOLUMN_THRESHOLD 80

using namespace std;

int main()
{
	ULARGE_INTEGER a;
	GetDiskFreeSpaceExA(NULL, NULL, &a, NULL);
	int disk_vol = round(a.QuadPart/(1024*1024*1024*1.0));
	cout << disk_vol << endl;
	
	if(disk_vol < DISK_VOLUMN_THRESHOLD)
		cout << "Could be VM" << endl;
	else
		cout << "OK. Disk volumn greater than " << DISK_VOLUMN_THRESHOLD << endl;
	
	return 0;
}

