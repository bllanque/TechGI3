#include <omp.h>
#include <stdio.h>

int main() {
	#pragma omp parallel
	{
		printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
		printf("I'll be back!\n");
	}
	printf("We are back...\n");
}