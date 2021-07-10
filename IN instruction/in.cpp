// use for detect VMWare
#include <iostream>

#define VMWARE_HYPERVISOR_MAGIC 0x564D5868
#define VMWARE_HYPERVISOR_PORT  0x5658
#define VMWARE_PORT_CMD_GETVERSION      10
#define VMWARE_PORT(cmd, eax, ebx, ecx, edx)                            \
        __asm__("inl (%%dx)" :                                          \
                        "=a"(eax), "=c"(ecx), "=d"(edx), "=b"(ebx) :    \
                        "0"(VMWARE_HYPERVISOR_MAGIC),                   \
                        "1"(VMWARE_PORT_CMD_##cmd),                     \
                        "2"(VMWARE_HYPERVISOR_PORT), "3"(UINT_MAX) :    \
                        "memory");

using namespace std;
						
int hypervisor_port_check(void)
{
        uint32_t eax, ebx, ecx, edx;
        VMWARE_PORT(GETVERSION, eax, ebx, ecx, edx);
        if (ebx == VMWARE_HYPERVISOR_MAGIC)
                return 1;               // Success - running under VMware
        else
                return 0;
}

int main()
{
	cout << "[IN instruction detect] ";
	if(hypervisor_port_check())
		cout << "VMWare detected!!" << endl;
	else
		cout << "Nothing" << endl;
}