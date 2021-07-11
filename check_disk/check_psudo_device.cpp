#include <iostream>
#include <Windows.h>
#include <Tchar.h>

using namespace std;


int main(){
	bool isVMware = false;
	
	const TCHAR *devices[] = {
		_T("\\\\.\\HGFS"),
		_T("\\\\.\\vmci"),
	};

	WORD iLength = sizeof(devices) / sizeof(devices[0]);
	for (int i = 0; i < iLength; i++)
	{
		HANDLE hFile = CreateFile(devices[i], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		TCHAR msg[256] = _T("");
		wcout << "Checking device " << devices[i] << "\t" ;
		
		if (hFile != INVALID_HANDLE_VALUE) {
			CloseHandle(hFile);
			isVMware = true;
			cout << "Detected\n";
		}
		else
			cout << "No\n";
	}
	if (isVMware)
		cout << "==> VMware DETECTED\n";
	else
		cout << "==> Nothing\n"; 
	
	return 0;
}