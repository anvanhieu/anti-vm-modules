// Ref: https://docs.microsoft.com/en-us/windows/win32/sysinfo/enumerating-registry-subkeys

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

using namespace std;

const TCHAR* VMWARE_SUBKEY[] = { _T("VMMemCtl"), _T("VMTools"),_T("VMTool"),  
                                 _T("vmhgfs"), _T("vmmouse"), _T("vm3dmp"),
                                _T("vmvss"), _T("vmxnet3ndis6"), _T("VMAUDIO")
                                // _T("VMBusHID"), _T("vmci"), _T("vmbus"),         // host with VMware installed have them too
                            };


bool QueryKeyAndCheckVMware(HKEY hKey)
{
    bool isVMware = false;
    int numOfSubkey = sizeof(VMWARE_SUBKEY) / sizeof(VMWARE_SUBKEY[0]);

    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys = 0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 

    DWORD i, retCode;

    TCHAR  achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 

    // Enumerate the subkeys, until RegEnumKeyEx fails.

    if (cSubKeys)
    {
        printf("\nNumber of subkeys: %d\n", cSubKeys);

        for (i = 0; i < cSubKeys; i++)
        {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                achKey,
                &cbName,
                NULL,
                NULL,
                NULL,
                &ftLastWriteTime);
            if (retCode == ERROR_SUCCESS)
            {
                
              for (int i = 0; i < numOfSubkey; i++)
                  if (!_tcscmp(achKey, VMWARE_SUBKEY[i]))
                  {
                      _tprintf(TEXT("(%d) %s\t\tDetected\n"), i + 1, achKey);
                      isVMware = true;
                  }
            }
        }
    }

    // Enumerate the key values. 

    if (cValues)
    {
        printf("\nNumber of values: %d\n", cValues);

        for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = RegEnumValue(hKey, i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                NULL,
                NULL);

            if (retCode == ERROR_SUCCESS)
            {
                _tprintf(TEXT("(%d) %s\n"), i + 1, achValue);
               
            }
        }
    }

    return isVMware;
}

int __cdecl _tmain()
{
    HKEY hTestKey;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SYSTEM\\ControlSet001\\services"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    {
        if (QueryKeyAndCheckVMware(hTestKey))
            cout << "===> VMware DETECTED!!" << endl;
        else
            cout << "===> Nothing!!" << endl;
    }

    

    RegCloseKey(hTestKey);
}