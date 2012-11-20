/*******************************************
 *
 * An example source module to accompany...
 * "Using POSIX Threads: 
 *      Programming with Pthreads"
 * Brad nichols, Dick Buttlar, Jackie Farrell
 * O'Reilly & Associates, Inc.
 *
 *********************************************
 * simple_processes.c
 *
 * Simple multi-process example.
 */

#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void do_one_thing(int *);
void do_another_thing(int *);
void do_wrap_up(int, int);

int   shared_mem_id;
int   *shared_mem_ptr;
int   *r1p;
int   *r2p;
int   v1=0;

main()
{

  pid_t  child1_pid, child2_pid;
  int  status=0;

  /* initialize shared memory segment */
  if ((shared_mem_id = shmget(IPC_PRIVATE, 
                      2*sizeof(int), 0777))<0) {

        perror("shmget failed");
  }


  if((shared_mem_ptr=(int *)shmat(shared_mem_id, 
                  (void *) 0, 0)) == (void *)-1)
    perror("shmat failed");

  r1p = shared_mem_ptr;  
  r2p = (shared_mem_ptr + 1);

  *r1p = 0;
  *r2p = 0;

  if ((child1_pid = fork()) == 0) {
    /* first child */
    do_one_thing(r1p);
    exit();
  }

  /* parent */
  if ((child2_pid = fork()) == 0) {
    /* second child */
    do_another_thing(r2p);
    exit();
  }

  /* parent */
  waitpid(child1_pid, &status, 0);
  waitpid(child2_pid, &status, 0);

  do_wrap_up(*r1p, *r2p);
  
}

void do_one_thing(int *pnum_times)
{
  int i, j, x;
  static int v2 = 0; 

  for (i = 0;  i < 4; i++) {
    v1++; v2++; printf("%d: v1=%d,v2=%d ",getpid(),v1,v2);
    sleep(1);
    printf("doing one thing\n"); 
    for (j = 0; j < 10000; j++) x = x + i;
    (*pnum_times)++;
  }

}

void do_another_thing(int *pnum_times)
{
  int i, j, x;
  static int v2 = 0; 
  
  for (i = 0;  i < 4; i++) {
    v1++; v2++; printf("%d: v1=%d,v2=%d ",getpid(),v1,v2);
    sleep(1);
    printf("doing another \n"); 
    for (j = 0; j < 10000; j++) x = x + i;
    (*pnum_times)++;
  }

}

void do_wrap_up(int one_times, int another_times)
{
  int total;

  total = one_times + another_times;
  printf("All done, one thing %d, another %d for a total of %d\n",
	one_times, another_times, total);
}

