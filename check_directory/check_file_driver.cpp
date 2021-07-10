// al-khaser

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
			_T("System32\\drivers\\vmnet.sys"),
			_T("System32\\drivers\\vmmouse.sys"),
			_T("System32\\drivers\\vmusb.sys"),
			_T("System32\\drivers\\vm3dmp.sys"),
			_T("System32\\drivers\\vmci.sys"),
			_T("System32\\drivers\\vmhgfs.sys"),
			_T("System32\\drivers\\vmmemctl.sys"),
			_T("System32\\drivers\\vmx86.sys"),
			_T("System32\\drivers\\vmrawdsk.sys"),
			_T("System32\\drivers\\vmusbmouse.sys"),
			_T("System32\\drivers\\vmkdb.sys"),
			_T("System32\\drivers\\vmnetuserif.sys"),
			_T("System32\\drivers\\vmnetadapter.sys"),
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
				cout << "Nothing\n";
		}

	if(isVMwareDetected)
		cout << "==> VMware DETECTED\n";
	else
		cout << "==> Not VMware\n";

	return 0;
}