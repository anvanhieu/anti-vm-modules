// Ref: https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemfirmwaretable
// build with VS Studio

#include <iostream>
#include <Windows.h>

using namespace std;

DWORD SIGNATURE = 'ACPI';
DWORD FIRMWARE_ID = 'TEPH';             // HPET 

int main()
{
    DWORD error = ERROR_SUCCESS;
    DWORD acpiDataSize = 0;
    BYTE* acpiData = NULL; // Defined in this link
    DWORD bytesWritten = 0;

    // Query size of ACPI data.
    acpiDataSize = GetSystemFirmwareTable(SIGNATURE, FIRMWARE_ID, NULL, 0);

    // Allocate memory for ACPI data
    acpiData = (BYTE*)HeapAlloc(GetProcessHeap(), 0, acpiDataSize);
    if (!acpiData) {
        error = ERROR_OUTOFMEMORY;
        HeapFree(GetProcessHeap(), 0, acpiData);
        return -1;
    }

    // Retrieve the ACPI table
    bytesWritten = GetSystemFirmwareTable(SIGNATURE, FIRMWARE_ID, acpiData, acpiDataSize);

    if (bytesWritten != acpiDataSize) {
        error = ERROR_INVALID_DATA;
        HeapFree(GetProcessHeap(), 0, acpiData);
        return -1;
    }

    cout << bytesWritten << endl;

    std::string needle("VMWARE", 6);


    std::string haystack(acpiData, acpiData + bytesWritten);  

    std::size_t n = haystack.find(needle);

    if (n == std::string::npos)
    {
        cout << "Not detect" << endl;
    }
    else
    {
        cout << "Found VMWARE at: " << n << endl
            << "==> VMware detected" << endl;
    }


    HeapFree(GetProcessHeap(), 0, acpiData);

    return 0;
}