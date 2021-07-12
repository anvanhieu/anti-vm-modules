// Ref: al-khaser

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <Tchar.h>
#include <shlwapi.h>

using namespace std;

BOOL Is_RegKeyExists(HKEY hKey, const TCHAR* lpSubKey)
{
	HKEY hkResult = NULL;
	TCHAR lpData[1024] = { 0 };
	DWORD cbData = MAX_PATH;

	if (RegOpenKeyEx(hKey, lpSubKey, NULL, KEY_READ, &hkResult) == ERROR_SUCCESS)
	{
		RegCloseKey(hkResult);
		return TRUE;
	}

	return FALSE;
}

bool vmware_reg_keys()
{
	bool isVMware = false;
	/* Array of strings of blacklisted registry keys */
	const TCHAR* szKeys[] = {
		_T("SOFTWARE\\VMware, Inc.\\VMware Tools"),
	};

	WORD dwlength = sizeof(szKeys) / sizeof(szKeys[0]);

	/* Check one by one */
	for (int i = 0; i < dwlength; i++)
	{
		TCHAR msg[256] = _T("");
		wcout << _T("Checking reg key ") << szKeys[i] << "\t\t";
		if (Is_RegKeyExists(HKEY_LOCAL_MACHINE, szKeys[i]))
		{
			cout << "Detected" << endl;
			isVMware = true;
		}
		else
			cout << "No" << endl;
	}
	return isVMware;
}

int main()
{
	cout << endl;
	if(vmware_reg_keys())
		cout << "==> VMWare DETECTED" << endl;
	else
		cout << "==> Nothing" << endl;
	return 0;
}

