#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

const unsigned long long RDTSC_THRESHOLD = 100;			// get value depending on my own PC/VM

static inline unsigned long long rdtsc_diff() {
	unsigned long long ret, ret2;
	unsigned eax, edx;
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	//int a = 10;
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret2  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	return ret2 - ret;
}


int cpu_rdtsc() {
	int i;
	unsigned long long avg = 0;
	for (i = 0; i < 10; i++) {
		avg = avg + rdtsc_diff();
		Sleep(500);
		// int junk;
		// for(int i = 0; i < 1000; i++)
			// junk = i++;
	}
	avg = avg / 10;
	printf("rdtsc avg: %llu", avg);
	return (avg < RDTSC_THRESHOLD && avg > 0) ? 0 : 1;
}

int main()
{
		if(cpu_rdtsc())
			printf("==> VMware Detected\n");
		else 
			printf("==> No\n");
	
	
	return 0;
}