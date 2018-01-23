#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <math.h>

double waster_time(long n)
{
	double res = 0;
	long i = 0;
	while(i <n * 200000) {
		i++;
		res += sqrt (i);
	}
	return res;
}
void setProcessToCpuList(int *cpulist, int len)
{

	cpu_set_t mask;
	cpu_set_t get;

	CPU_ZERO(&mask);
	CPU_ZERO(&get);

	for (int i= 0; i < len; i++) {
		CPU_SET(cpulist[i], &mask);
	}

	if(sched_setaffinity(0, sizeof(mask), &mask) < 0 ) {
		printf("set process cpu affinity failed\n");
	}

}

int main(int argc, char **argv)
{
	int cpu_online = sysconf(_SC_NPROCESSORS_ONLN);
	int gpucardnum = 8;
	int averagecpulist = cpu_online / gpucardnum;
	int cpulist[10];
	for (int i = 0; i < averagecpulist; i++) {
		cpulist[i] = i;
	}
	setProcessToCpuList(cpulist, averagecpulist);
	printf("result1: %f\n", waster_time(20000));

	for (int i = 0; i < averagecpulist; i++) {
		cpulist[i] = i + averagecpulist;
	}
	setProcessToCpuList(cpulist, averagecpulist);
	printf("result2: %f\n", waster_time(20000));
	return 0;
}
