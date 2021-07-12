// Ref: al-khaser

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <Tchar.h>
#include <shlwapi.h>

using namespace std;

BOOL Is_RegKeyValueExists(HKEY hKey, const TCHAR* lpSubKey, const TCHAR* lpValueName, const TCHAR* search_str)
{
	HKEY hkResult = NULL;
	TCHAR lpData[1024] = { 0 };
	DWORD cbData = MAX_PATH;

	if (RegOpenKeyEx(hKey, lpSubKey, NULL, KEY_READ, &hkResult) == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(hkResult, lpValueName, NULL, NULL, (LPBYTE)lpData, &cbData) == ERROR_SUCCESS)
		{
			if (StrStrI((PCTSTR)lpData, search_str) != NULL)
			{
				RegCloseKey(hkResult);
				return TRUE;
			}
		}
		RegCloseKey(hkResult);
	}
	return FALSE;

}

bool vmware_reg_key_value()
{
	bool isVMware = false;
	/* Array of strings of blacklisted registry key values */
	const TCHAR *szEntries[][3] = {
		{ _T("HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 0\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0"), _T("Identifier"), _T("VMWARE") },
		{ _T("HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 1\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0"), _T("Identifier"), _T("VMWARE") },
		{ _T("HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 2\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0"), _T("Identifier"), _T("VMWARE") },
		{ _T("SYSTEM\\ControlSet001\\Control\\SystemInformation"), _T("SystemManufacturer"), _T("VMWARE") },
		{ _T("SYSTEM\\ControlSet001\\Control\\SystemInformation"), _T("SystemProductName"), _T("VMWARE") },
	};

	WORD dwLength = sizeof(szEntries) / sizeof(szEntries[0]);

	for (int i = 0; i < dwLength; i++)
	{
		TCHAR msg[256] = _T("");
		wcout << _T("Checking reg key ") << szEntries[i][0] << "\t\t";
		if (Is_RegKeyValueExists(HKEY_LOCAL_MACHINE, szEntries[i][0], szEntries[i][1], szEntries[i][2]))
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
	if(vmware_reg_key_value())
		cout << "==> VMWare DETECTED" << endl;
	else
		cout << "==> Nothing" << endl;
	return 0;
}