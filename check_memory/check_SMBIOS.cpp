// Ref: https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemfirmwaretable
// build with VS Studio

#include <iostream>
#include <Windows.h>

using namespace std;

struct RawSMBIOSData
{
    BYTE    Used20CallingMethod;
    BYTE    SMBIOSMajorVersion;
    BYTE    SMBIOSMinorVersion;
    BYTE    DmiRevision;
    DWORD    Length;
    BYTE    SMBIOSTableData[];
};

int main()
{
    DWORD error = ERROR_SUCCESS;
    DWORD smBiosDataSize = 0;
    RawSMBIOSData* smBiosData = NULL; // Defined in this link
    DWORD bytesWritten = 0;

    // Query size of SMBIOS data.
    smBiosDataSize = GetSystemFirmwareTable('RSMB', 0, NULL, 0);

    // Allocate memory for SMBIOS data
    smBiosData = (RawSMBIOSData*)HeapAlloc(GetProcessHeap(), 0, smBiosDataSize);
    if (!smBiosData) {
        error = ERROR_OUTOFMEMORY;
        HeapFree(GetProcessHeap(), 0, smBiosData);
        return -1;
    }

    // Retrieve the SMBIOS table
    bytesWritten = GetSystemFirmwareTable('RSMB', 0, smBiosData, smBiosDataSize);

    if (bytesWritten != smBiosDataSize) {
        error = ERROR_INVALID_DATA;
        HeapFree(GetProcessHeap(), 0, smBiosData);
        return -1;
    }

    
    int TableDataLen = bytesWritten -
        sizeof(smBiosData->Used20CallingMethod) -
        sizeof(smBiosData->SMBIOSMajorVersion) -
        sizeof(smBiosData->SMBIOSMinorVersion) -
        sizeof(smBiosData->DmiRevision) -
        sizeof(smBiosData->Length);

    cout << TableDataLen << endl;

    std::string needle("VMware", 6);
    BYTE* TableAddress = smBiosData->SMBIOSTableData;

   
    std::string haystack(TableAddress, TableAddress + TableDataLen);

    std::size_t n = haystack.find(needle);

    if (n == std::string::npos)
    {
        cout << "Not detect" << endl;
    }
    else
    {
        cout << "Found VMware at: " << n << endl
            << "==> VMware detected" << endl;
    }


    HeapFree(GetProcessHeap(), 0, smBiosData);

    return 0;
}