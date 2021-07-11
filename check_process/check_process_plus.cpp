// Ref: https://docs.microsoft.com/en-us/windows/win32/psapi/enumerating-all-processes
// adding some process 
// g++ <> -lpsapi

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <psapi.h>
#include <string>


std::string VM_PROCESS_STRING[] = {"vmtoolsd.exe", "vm3dservice.exe", "vmwaretray.exe", "vmwaretray.exe", "VGAuthService.exe", "vmacthlp.exe"};


bool isVMwareProcess( DWORD processID )
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    
	//Compare process name with VMware vmtool  process name.
	for(std::string item : VM_PROCESS_STRING)
		if(std::string(szProcessName) == item)
		{
			_tprintf( TEXT("%s  (PID: %u)\n"), szProcessName, processID );
			CloseHandle( hProcess );
			return true;
		}
	
	// Release the handle to the process.
    CloseHandle( hProcess );
	return false;
}

int main( void )
{
    // Get the list of process identifiers.

    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return 1;
    }


    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.

    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
            if(isVMwareProcess( aProcesses[i] ))
				std::cout << "VM DETECTED\n";
        }
    }

    return 0;
}
