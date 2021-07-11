// Ref: https://www.cyberbit.com/blog/endpoint-security/anti-vm-and-anti-sandbox-explained/
// al-khaser
// g++ -fPIC -static -static-libgcc -static-libstdc++ check_file_dll.cpp -o check_file_dll -lshlwapi 

#include <windows.h>
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <shlwapi.h>
#include <Tchar.h>

using namespace std;

BOOL is_FileExists(TCHAR* szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES) && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

int main(){
	
	bool isVMwareDetected = false;
	
	const TCHAR* szPaths[] = {
			_T("System32\\vm3dgl.dll"),
			_T("System32\\vm3dgl.dll"),
			_T("System32\\vmdum.dll"),
			_T("System32\\vm3dver.dll"),
			_T("System32\\vmtray.dll"),
			_T("System32\\VMToolsHook.dll"),
			_T("System32\\vmmousever.dll"),
			_T("System32\\vmhgfs.dll"),
			_T("System32\\vmGuestLib.dll"),
			_T("System32\\VmGuestLibJava.dll"),
			_T("System32\\vmhgfs.dll"),
		};

		/* Getting Windows Directory */
		WORD dwlength = sizeof(szPaths) / sizeof(szPaths[0]);
		TCHAR szWinDir[MAX_PATH] = _T("");
		TCHAR szPath[MAX_PATH] = _T("");
		PVOID OldValue = NULL;

		GetWindowsDirectory(szWinDir, MAX_PATH);
		
		 /* Check one by one */
		for (int i = 0; i < dwlength; i++)
		{
			PathCombine(szPath, szWinDir, szPaths[i]);
			TCHAR msg[256] = _T("");
			wcout << _T("Checking file ") << szPath << "\t\t";
			if (is_FileExists(szPath)){
				cout << "Detected\n";
				isVMwareDetected = true;
			}
			else
				cout << "No\n";
		}

	if(isVMwareDetected)
		cout << "==> VMware DETECTED\n";
	else
		cout << "==> Not VMware\n";

	return 0;
}
