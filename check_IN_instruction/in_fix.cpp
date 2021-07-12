// Ref: https://brundlelab.wordpress.com/2012/10/21/detecting-vmware/
// build in vs studio 

#include <stdio.h>
#include <windows.h>


#define OOPS_PRIVILEGED_INSTRUCTION 0xC0000096


int main(int argc, char* argv[])
{
	unsigned int vm_flag = 0;

	/* The check will set the VM Flag to ZERO if successful */

	__try
	{
		__asm
		{
			mov eax, 0x564D5868; ascii: VMXh
			mov edx, 0x5658; ascii: VX(port)
			in eax, dx; input from Port
			cmp ebx, 0x564D5868; ascii: VMXh
			setz ecx; if successful->flag = 0
			mov vm_flag, ecx
		}

		if (vm_flag != 0)			// experiment --> value not same as theory
			printf("Inside VMWARE!!!\n");
	}
	__except (GetExceptionCode() == OOPS_PRIVILEGED_INSTRUCTION ?
		EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		printf("NOT detected\n");
		return -1;
	}

	

	return 0;
}