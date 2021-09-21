#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <time.h>
#include <stdatomic.h>

int num_thread;
long loop;
volatile atomic_ullong global_hit = 0;
volatile atomic_ullong cur_loop = 0;


struct timespec start, end;

void sighandler(int signum){
	
	clock_gettime(CLOCK_REALTIME, &end);
	
    if (end.tv_sec - start.tv_sec < 1){
        exit(0);
    }
	else{
		printf("\nglobal_hit:\t%llu\n", global_hit);
		printf("cur_loop:\t%llu\n", cur_loop);
		printf("pi = %.8lf\n", 4. * ((double) global_hit / cur_loop));
	}
	clock_gettime(CLOCK_REALTIME, &start);
}

void thread(void* rand_buffer) {
	double x, y, rand_d;
	unsigned long long local_loop = loop / num_thread;

	for(unsigned long long i = 0; i < local_loop; i++) {	
		drand48_r(rand_buffer, &rand_d);
		x = rand_d;
		drand48_r(rand_buffer, &rand_d);
		y = rand_d;

		if((x * x + y * y) < 1.0)
			atomic_fetch_add(&global_hit, 1);
		atomic_fetch_add(&cur_loop, 1);
	}
}


int main(int argc, char **argv) {
	clock_gettime(CLOCK_REALTIME, &start);
	pthread_t id[128];
	struct drand48_data* rand_buffer[128];
	double pi = 0.0;
	double rand_d;

	loop = atol(argv[1]);
	num_thread = atoi(argv[2]);
	assert(num_thread < 128);

	signal(SIGINT, sighandler);

	
	for(int i = 0; i < num_thread; i++) {
		rand_buffer[i] = aligned_alloc(64, sizeof(struct drand48_data));
		srand48_r(rand(), rand_buffer[i]);
		drand48_r(rand_buffer[i], &rand_d);
		//printf("@buffer = %p\n", rand_buffer[i]);
		//printf("thread%d's seed = %f\n", i, rand_d);
		pthread_create(&id[i], NULL, (void *)thread, rand_buffer[i]);
	}

	for(int i = 0; i < num_thread; i++)
		pthread_join(id[i], NULL);

	pi = 4. * ((double)global_hit / loop);
	printf("pi = %.8lf\n", pi);
	return 0;
}