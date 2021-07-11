// Ref: pafish

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

const unsigned long long RDTSC_VM_EXIT_THRESHOLD = 1000;

static inline unsigned long long rdtsc_diff_vmexit() {
	unsigned long long ret, ret2;
	unsigned eax, edx;
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	/* vm exit forced here. it uses: eax = 0; cpuid; */
	__asm__ volatile("cpuid" : /* no output */ : "a"(0x00));
	/**/
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret2  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	return ret2 - ret;
}


int cpu_rdtsc_force_vmexit() {
	int i;
	unsigned long long avg = 0;
	for (i = 0; i < 10; i++) {
		avg = avg + rdtsc_diff_vmexit();
		
	}
	avg = avg / 10;
	printf("rdtsc_exit avg: %llu", avg);
	return (avg < RDTSC_VM_EXIT_THRESHOLD && avg > 0) ? 0 : 1;
}


int main()
{
		if(cpu_rdtsc_force_vmexit())
			printf("==> VMware Detected\n");
		else 
			printf("==> No\n");
	
	return 0;
}