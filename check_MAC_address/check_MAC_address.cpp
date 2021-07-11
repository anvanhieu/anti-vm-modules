// Ref: https://evasions.checkpoint.com/techniques/network.html
// 		al-khaser 
//  g++ check_MAC_address.cpp  -o check_MAC_address -liphlpapi

#include <iostream>
#include <Windows.h>
#include <iphlpapi.h>

using namespace std;

BYTE COMMON_MAC_VMWARE_HEAD[4][3] = { {0x00, 0x05, 0x69 }, {0x00, 0x0C, 0x29}, {0x00, 0x1C, 0x14}, {0x00, 0x50, 0x56} };


int check_mac_vmware(BYTE* mac_addr, bool needLoop)
{
	int len = sizeof(COMMON_MAC_VMWARE_HEAD) / sizeof(COMMON_MAC_VMWARE_HEAD[0]);
				for (int i = 0; i < len; i++)
				{
					bool isMAC = true;
					for (int j = 0; j < 3; j++)
						if (mac_addr[j] != COMMON_MAC_VMWARE_HEAD[i][j])
						{
							isMAC = false;
							break;
						}
					if (isMAC) 
					{
						needLoop = false;
						return i;  // index in COMMON_MAC_VMWARE_HEAD
					}
				}
	return -1;
}

int main()
{
	bool isVMWare = false;
	BOOL bResult = FALSE;
	PIP_ADAPTER_INFO pAdapterInfo, pAdapterInfoPtr;
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	pAdapterInfo = (PIP_ADAPTER_INFO)HeapAlloc(GetProcessHeap(), 0, sizeof(IP_ADAPTER_INFO));
	
	if (pAdapterInfo == NULL)
	{
		cout << "Error allocating memory needed to call GetAdaptersinfo.\n";
		return 0;
	}

	DWORD dwResult = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen); 

	// Make an initial call to GetAdaptersInfo to get the necessary size into the ulOutBufLen variable
	if (dwResult == ERROR_BUFFER_OVERFLOW)
	{
		HeapFree(GetProcessHeap(), 0, pAdapterInfo);
		pAdapterInfo = (PIP_ADAPTER_INFO)HeapAlloc(GetProcessHeap(), 0, ulOutBufLen);
		if (pAdapterInfo == NULL) {
			printf("Error allocating memory needed to call GetAdaptersinfo\n");
			return 1;
		}

		dwResult = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen);
	}

	if (dwResult == ERROR_SUCCESS)
	{
		pAdapterInfoPtr = pAdapterInfo;
		bool needLoop = true;
		while (pAdapterInfoPtr && needLoop)
		{
			if (pAdapterInfoPtr->AddressLength == 6 && check_mac_vmware(pAdapterInfoPtr->Address, &needLoop))
			{
				cout << "VMware detected" << endl;
			}
			pAdapterInfoPtr = pAdapterInfoPtr->Next;
		}
	}
	return 0;
}