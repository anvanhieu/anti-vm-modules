// get rdtsc from 30 times running --> get threshold

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static inline unsigned long long rdtsc_diff() {
	unsigned long long ret, ret2;
	unsigned eax, edx;
	
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret2  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	return ret2 - ret;
}

unsigned long long cpu_rdtsc() {
	int i;
	unsigned long long avg = 0;
	for (i = 0; i < 10; i++) {
		avg = avg + rdtsc_diff();
		Sleep(500);
	}
	avg = avg / 10;
	printf("rdtsc avg: %llu\n", avg);
	return avg;
}

int main()
{
	unsigned long long sum = 0;
	for(int i = 0; i < 30; i++)
	{
		sum += cpu_rdtsc();
		Sleep(5000);
	}
	
	printf("==> AFTER 30 TIMES avg: %llu\n", sum / 30);
	
	return 0;
}